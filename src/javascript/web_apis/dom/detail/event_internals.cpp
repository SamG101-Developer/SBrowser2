#include "event_internals.hpp"
#include "dom/events/event.hpp"

#include <ext/assert.hpp>
#include <ext/functional.hpp>
#include <ext/ranges.hpp>

#include <web_apis/dom/abort/abort_signal.hpp>
#include <web_apis/dom/nodes/shadow_root.hpp>
#include <web_apis/dom/nodes/window.hpp>

#include <web_apis/dom/detail/shadow_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/empty.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/slice.hpp>

auto dom::detail::event_internals::flatten_more(
        std::variant<ext::boolean, ext::string_any_map> options)
        -> ext::string_any_map
{
    // return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    return std::holds_alternative<ext::boolean>(options)
           ? ext::string_any_map{std::make_pair("capture", std::get<ext::boolean>(options))}
           : std::get<ext::string_any_map>(options);
}


auto dom::detail::event_internals::flatten(
        std::variant<ext::boolean, ext::string_any_map> options)
        -> ext::boolean
{
    // return the boolean if a boolean value is being stored in the variant, otherwise the capture option of the map
    return std::holds_alternative<ext::boolean>(options)
           ? std::get<ext::boolean>(options)
           : std::get<ext::string_any_map>(options).at("capture").value().to<ext::boolean>();
}


auto dom::detail::event_internals::add_event_listener(
        nodes::event_target* event_target,
        ext::string_any_map_view event_listener)
        -> void
{
    // get the abort signal from the event listener, and default the object to nullptr if it doesn't exist in the map
    auto* signal = event_listener.at("signal").value_to_or<abort::abort_signal*>(nullptr);

    // return if
    //  - there is no callback - invoking the event listener would have no effect and would waste cycles
    //  - there is a signal that has already aborted, - no need for the event listener to exist
    //  - the event listener is already stored in the event listeners list - no duplicates allowed
    if (event_listener.at("callback").empty()
            || signal && signal->aborted()
            || std::ranges::find(event_target->m_event_listeners, event_listener) != event_target->m_event_listeners.end())
        return;

    // append the event listener to the event listeners list and if there is an abort signal, add an abort algorithm
    // that removes the event_listener from the event_target->m_event_listeners list
    event_target->m_event_listeners.push_back(event_listener);
    if (signal)
        signal->m_abort_algorithms.push_back([&event_listener, &event_target] {remove_event_listener(event_target, event_listener);});
}


auto dom::detail::event_internals::remove_event_listener(
        nodes::event_target* event_target,
        ext::string_any_map_view event_listener)
        -> void
{
    // set the removed attribute of the listener to true (so if the listener is being held in a variable it can be
    // detected that it is no longer in use)
    event_listener.insert_or_assign("removed", false);

    // alias the callback type for convenience, and remove all event listeners that have a matching callback, type and
    // capture attribute to event_listener
    using callback_t = typename nodes::event_target::event_listener_callback_t;

    auto event_listener_equality_check = [event_listener](const ext::string_any_map& existing_listener)
    {
        return existing_listener.at("callback").has_value_and_equals(event_listener.at("callback")->to<callback_t>())
               && existing_listener.at("type").has_value_and_equals(event_listener.at("type")->to<ext::string_view>())
               && existing_listener.at("capture").has_value_and_equals(event_listener.at("capture")->to<ext::boolean>());
    };

    event_target->m_event_listeners |= ranges::views::remove_if(event_listener_equality_check);
}


auto dom::detail::event_internals::remove_all_event_listeners(
        nodes::event_target* event_target)
        -> void
{
    // iterate over the event listeners, and remove each one from the event target sing the predefined removal
    // algorithm defined above (not just popping items from a list)
    for (const ext::string_any_map& existing_listener: event_target->m_event_listeners)
        remove_event_listener(event_target, existing_listener);
}


auto dom::detail::event_internals::dispatch(
        events::event* event,
        nodes::event_target* target)
        -> ext::boolean
{
    event->m_dispatch_flag = true;
    auto is_activation_event = event->type() == "click"; // && dynamic_cast<ui_events::events::mouse_event*>(event)
    nodes::event_target* activation_target = is_activation_event ? target : nullptr;;
    nodes::event_target* related_target = detail::shadow_internals::retarget(event->related_target(), target);
    ext::boolean clear_targets = false;

    if (target != related_target || target == event->related_target())
    {
        // the current parent is the target (make the 1 loop, rather than have initialization scripts and then the loop
        // after with variables changing ie roll the unrolled single execution for target by merging it with the parent
        // script)
        auto* parent = target;
        auto* parent_node = dynamic_cast<nodes::node*>(parent);

        do
        {
            // the related target is the event's related target, transformed to be retargeted against the current parent
            // node
            related_target = shadow_internals::retarget(event->related_target(), parent);

            // the 'slot_in_closed_tree' always defaults to false, and can be changed if the 'parent' is an assigned
            // slottable. the touch targets are the event's touch targets, transformed to be retargeted against the
            // current parent
            auto slot_in_closed_tree = ext::boolean::FALSE();
            auto touch_targets = *event->touch_targets()
                    | ranges::views::transform(ext::bind_back(shadow_internals::retarget, std::move(parent)));

            // if the 'parent' is assigned (and implicitly therefore a slottable), then assert that the parent is a slot
            // too. the slot is in a closed tree if the mode of the ShadowRoot is "closed" TODO : why
            if (shadow_internals::is_assigned(parent_node))
            {
                ext::assert_true(shadow_internals::is_slot(parent_node));
                slot_in_closed_tree = shadow_internals::is_root_shadow_root(parent_node)->mode() == "closed";
            }

            // if the parent is a Window object, or the root of 'target' is a shadow including ancestor of the current
            // 'parent' (not necessarily the parent of 'target'), then append a struct to the event's path, where the
            // shadow adjusted target is nullptr, because the 'target' is attached to a tree that the 'parent' isn't
            if (dynamic_cast<nodes::window*>(parent) || shadow_internals::is_shadow_including_ancestor(tree_internals::root(dynamic_cast<nodes::node*>(target)), parent_node))
            {
                activation_target = is_activation_event && !activation_target && event->bubbles() ? parent : activation_target;
                append_to_event_path(event, parent, nullptr, related_target, touch_targets, slot_in_closed_tree);
            }

            // if the 'parent' is the 'related_target', then set the 'parent', and its Node cast to nullptr; this will
            // stop the 'get_the_parent(...)' algorithm being called, meaning that the loop will terminate (guard
            // condition to the do-while checks that a parent exists for next iteration)
            else if (parent == related_target)
            {
                parent = nullptr;
                parent_node = nullptr;
            }

            // otherwise, a struct with the shadow adjusted target set to the target' is appended to the Event's path;
            // the TODO : shadows
            else
            {
                activation_target = is_activation_event && !activation_target ? target : activation_target;
                append_to_event_path(event, parent, target, related_target, touch_targets, slot_in_closed_tree);
            }

            // set the 'parent_event_target' to the next parent, determined by executing the EventTarget's
            // 'get_the_parent(...)' method; do this by setting the underlying value of the pointer, as this will
            // automatically update the 'parent_node' object, which is holding a Node cast of the parent
            if (parent)
                *parent = *parent->get_the_parent(event);

        } while (parent); // iterate until the parent is nullptr (parent is the related target)

        // the 'clear_targets_struct' is the last struct in the event path with a shadow adjusted target; if the target,
        // related target, or any touch targets of this struct are nodes who have ShadowRoot roots, then the target and
        // related target of the event have to be cleared once the event has finished traversing its path
        auto* clear_targets_struct = ranges::last_where(*event->path(), [](event_path_struct* s) {return s->shadow_adjusted_target;});
        auto  clear_targets_list = clear_targets_struct->touch_targets + ext::vector<nodes::event_target*>{clear_targets_struct->shadow_adjusted_target, clear_targets_struct->related_target};
        clear_targets = ranges::any_of(
                clear_targets_list | ranges::views::cast_all_to<nodes::node>(),
                [](nodes::node* node) {return shadow_internals::is_root_shadow_root(node);});

        // for the capturing phase, the event traverses from the top-most node (root), to the target node - the event
        // path is reversed and iterated over, invoking each listener in the capturing phase. the event phase is set to
        // AT_TARGET or CAPTURING_PHASE depending on if the current target is the final target or not
        for (auto* event_path_struct: *event->path() | ranges::views::reverse)
        {
            event->event_phase = event_path_struct->shadow_adjusted_target ? events::event::AT_TARGET : events::event::CAPTURING_PHASE;
            invoke(event_path_struct, event, events::event::CAPTURING_PHASE);
        }

        // for the bubbling phase, the event traverses from the target node to the top-most node (root), if the event
        // can bubble - the event path us iterated over, invoking each listener in the bubbling phase. the event phase
        // is set to AT_TARGET or CAPTURING_PHASE depending on if the current target is the final target or not
        for_if (event->bubbles(), auto* event_path_struct: *event->path())
        {
            event->event_phase = event_path_struct->shadow_adjusted_target ? events::event::AT_TARGET : events::event::BUBBLING_PHASE;
            invoke(event_path_struct, event, events::event::BUBBLING_PHASE);
        }
    }

    // reset attributes of the event that relate to the current traversal of the event - the phase of the event
    // determining where in the DOM tree it currently is, the current target of the event, and the entire traversal path
    // of the event
    event->event_phase = events::event::NONE;
    event->current_target = nullptr;
    event->path->clear();

    // reset the dispatch and propagation flags of the event, making the event in teh correct state to be re-emitted -
    // the dispatch flag is checked before dispatching, and the propagation flags are reset so that the event doesn't
    // unexpectedly stop straight away / after first target
    event->m_dispatch_flag = false;
    event->m_stop_propagation_flag = false;
    event->m_stop_immediate_propagation_flag = false;

    // if the other targets are to be cleared, then set the final target and the related to nullptr, before clearing the
    // touch targets - this gives the option of maintaining the targets for re-emission, or clearing the targets for a
    // completely new purpose of the event
    if (clear_targets)
    {
        event->target = event->related_target = nullptr;
        event->touch_targets->clear();
    }

    // if there is at activation target, then execute the activation behaviour of the activation target, passing the
    // event as the parameter
    if (activation_target)
        activation_target->m_dom_behaviour.activation_behaviour(event);

    // the dispatch was successful if the event wasn't cancelled during path traversal
    return !event->m_canceled_flag;
}


auto dom::detail::event_internals::append_to_event_path(
        events::event* event,
        nodes::event_target* invocation_target,
        nodes::event_target* shadow_adjusted_target,
        nodes::event_target* related_target,
        ranges::any_view<event_path_struct*> touch_targets,
        ext::boolean_view slot_in_closed_tree)
        -> void
{
    // the 'invocation_target' is in the shadow tree if it has a ShadowRoot root node, and the 'invocation_target' is
    // the root of a closed tree if it is a "closed" ShadowRoot node itself
    ext::boolean invocation_target_in_shadow_tree = shadow_internals::is_root_shadow_root(dynamic_cast<nodes::node*>(invocation_target));
    ext::boolean root_of_closed_tree = dynamic_cast<nodes::shadow_root*>(invocation_target)->mode() == "closed";

    // emplace a new 'event_path_struct' into the event's path, casting the range to a vector
    event->path->emplace_back(new event_path_struct
    {
        .invocation_target = invocation_target,
        .shadow_adjusted_target = shadow_adjusted_target,
        .related_target = related_target,
        .touch_targets = touch_targets | ranges::to<ext::vector<event_path_struct*>>(),
        .invocation_target_in_shadow_tree = invocation_target_in_shadow_tree,
        .root_of_closed_tree = root_of_closed_tree,
        .slot_in_closed_tree = slot_in_closed_tree
    });
}


auto dom::detail::event_internals::invoke(
        event_path_struct* s,
        events::event* event,
        uchar phase)
        -> void
{
    // the viable structs are the struct in the event path that are inclusively preceding 's', and have a shadow
    // adjusted target set
    auto viable_structs =
            ranges::subrange(event->path()->begin(), ranges::find(*event->path(), s))
            | ranges::views::filter([](event_path_struct* viable_s) {return viable_s->shadow_adjusted_target;});

    // set the target to the 'viable_struct''s shadow adjusted target, and copy the related and touch targets from the
    // 's'. if the event's strop propagation flag has been set, then return early and don't invoke the callback, as the
    // event is no longer allowed to traverse the DOM tree
    event->target = viable_structs.back()->shadow_adjusted_target;
    event->related_target = s->related_target;
    event->touch_targets = &s->touch_targets;
    return_if(event->m_stop_propagation_flag);

    // call 'inner_invoke(...)' with the event, a range copy of the event's listeners, the phase (capturing / bubbling),
    // and if the invoation target is in a shadow tree or not
    auto listeners = ranges::ref_view(event->current_target->m_event_listeners);
    inner_invoke(event, listeners, phase, s->invocation_target_in_shadow_tree);
}


auto dom::detail::event_internals::inner_invoke(
        events::event* event,
        ranges::any_view<ext::string_any_map> event_listeners,
        uchar phase,
        ext::boolean_view invocation_target_in_shadow_tree)
        -> void
{
    // loop through all the event listeners that have the same type as the event, and that match the capture or bubbling
    // phase of the event ie a 'capturing' listener can only be invoked for an event in the 'CAPTURING_PHASE', and a
    // listener whose 'capturing' attribute is set to false can only be invoked for an event in the 'BUBBLING_PHASE'
    for (ext::string_any_map_view listener: event_listeners
            | ranges::views::filter([event](ext::string_any_map_view listener) {return listener.at("type").value().to<ext::string>() == event->type();})
            | ranges::views::filter([phase](ext::string_any_map_view listener) {return listener.at("capture").value().to<bool>() && phase == events::event::CAPTURING_PHASE;})
            | ranges::views::filter([phase](ext::string_any_map_view listener) {return !listener.at("capture").value().to<bool>() && phase == events::event::BUBBLING_PHASE;}))
    {
        // if the event listener's 'once' attribute is set to true, then remove the event listener from the
        // EventTarget's listener list (not the copied range, as this won't affect the actual EventTarget)
        if (listener.at("once").value().to<bool>())
            event->current_target()->m_event_listeners |= ranges::views::remove(listener);

        // type alias the callback type for convenience, and get the associated javascript realm for the listener's
        // callback function object
        using callback_t = typename nodes::event_target::event_listener_callback_t;
        JS_REALM_GET_ASSOCIATED(v8pp::to_v8(v8::Isolate::GetCurrent(), listener.at("callback").value().to<callback_t>()));

        // if the global object for the associated realm is a Window object, then save its 'current_event' attribute,
        // and set the attribute to the 'event', if the invocation target is in a shadow tree TODO : why?
        events::event* current_event = nullptr;
        if (auto* global = v8pp::from_v8<nodes::window*>(associated_agent, associated_global_object))
        {
            current_event = global->current_event();
            global->current_event = invocation_target_in_shadow_tree ? event : global->current_event();
        }

        // set the event's passive listener flag if the listener is a passive listener, invoke the callback with the
        // event type and event object, and then unset the passive listener flag in the event object, as there isn't a
        // known passive listener whose callback is currently executing
        event->m_in_passive_listener_flag = listener.at("passive")->to<bool>();
        listener.at("callback")->to<callback_t>()("handleEvent", event);
        event->m_in_passive_listener_flag = ext::boolean::FALSE();

        // restore the current event back to the Window associated global object
        if (auto* global = v8pp::from_v8<nodes::window*>(associated_agent, associated_global_object))
            global->current_event = current_event;

        // return if the stop immediate propagation flag is set, as this disallows any more listeners from being called
        // on the event, even if they are on the same target
        return_if(event->m_stop_immediate_propagation_flag);
    }
}


template <inherit<dom::events::event> T>
auto dom::detail::event_internals::fire_event(
        ext::string&& e,
        nodes::event_target* target,
        ext::string_any_map&& init)
        -> ext::boolean
{
    // create a new event of type T, setting the event type and options, and then dispatch it to 'target'
    auto* event = new T{std::move(e), std::move(init)};
    return dispatch(event, target);
}