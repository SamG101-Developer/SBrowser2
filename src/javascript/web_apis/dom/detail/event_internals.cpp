#include "event_internals.hpp"

#include "ext/assertion.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/hashing.hpp"
#include "ext/keywords.hpp"
#include "ext/ranges.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/events/event.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/window.hpp"

#include "event_timing/detail/timing_internals.hpp"
#include "event_timing/performance_event_timing.hpp"

#include "hr_time/detail/time_internals.hpp"
#include "indexed_db/events/idb_version_change_event.hpp"
#include "pointer_events/pointer_event.hpp"
#include "touch_events/touch_event.hpp"

#include <fmt/format.h>
#include <range/v3/to_container.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/empty.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/slice.hpp>


auto dom::detail::flatten_more(
        event_listener_options_t&& options)
        -> ext::map<ext::string, ext::any>
{
    // return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    return ext::holds_alternative<ext::boolean>(std::move(options))
           ? ext::map<ext::string, ext::any>{std::make_pair("capture", ext::get<ext::boolean>(std::move(options)))}
           : ext::get<ext::map<ext::string, ext::any>>(std::move(options));
}


auto dom::detail::flatten(
        event_listener_options_t&& options)
        -> ext::boolean
{
    // return the boolean if a boolean value is being stored in the variant, otherwise the capture option of the map
    return ext::holds_alternative<ext::boolean>(std::move(options))
           ? ext::get<ext::boolean>(std::move(options))
           : ext::get<ext::map<ext::string, ext::any>>(options).at("capture").to<ext::boolean>();
}


auto dom::detail::remove_all_event_listeners(
        nodes::event_target* const event_target)
        -> void
{
    // iterate over the event listeners, and remove each one from the event target sing the predefined removal
    // algorithm defined above (not just popping items from a list)
    for (ext::map<ext::string, ext::any>& existing_listener: event_target->m_event_listeners)
        event_target->remove_event_listener(
                existing_listener.at("type").to<ext::string>(),
                existing_listener.at("callback").to<detail::event_listener_callback_t>(),
                std::move(existing_listener));
}


auto dom::detail::dispatch(
        events::event* const event,
        nodes::event_target* const target)
        -> ext::boolean
{
    event->d_func()->dispatch_flag = true;

    /* LARGEST_CONTENTFUL_PAINT BEGIN */
    JS_REALM_GET_RELEVANT(target);
    if (auto* window = v8pp::from_v8<nodes::window*>(target_relevant_agent, target_relevant_global_object);
            window != nullptr
            && event->d_func()->type() == "scroll"
            && event->d_func()->is_trusted())
        window->d_func()->has_dispatched_scroll_event = true;
    /* LARGEST_CONTENTFUL_PAINT END */

    /* EVENT_TIMING BEGIN */
    auto interaction_id = event_timing::detail::compute_interaction_id(event);
    auto entry_timing = event_timing::detail::initialize_event_timing(event, hr_time::detail::current_hr_time(target_relevant_global_object), std::move(interaction_id));
    /* EVENT_TIMING END */

    const auto is_activation_event = event->d_func()->type == "click"; // && dynamic_cast<ui_events::events::mouse_event*>(event)
    nodes::event_target* activation_target = is_activation_event ? target : nullptr;
    const nodes::event_target* related_target = detail::retarget(event->d_func()->related_target, target);
    ext::boolean clear_targets = false;

    if (target != related_target || target == event->d_func()->related_target)
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
            related_target = retarget(event->d_func()->related_target, parent);

            // the 'slot_in_closed_tree' always defaults to false, and can be changed if the 'parent' is an assigned
            // slottable. the touch targets are the event's touch targets, transformed to be retargeted against the
            // current parent
            auto slot_in_closed_tree = false;
            auto touch_targets = event->d_func()->touch_targets | ranges::views::transform(BIND_BACK(retarget, parent));

            // if the 'parent' is assigned (and implicitly therefore a slottable), then assert that the parent is a slot
            // too. the slot is in a closed tree if the mode of the ShadowRoot is "closed" TODO : why
            if (is_assigned(parent_node))
            {
                ASSERT(is_slot(parent_node));
                slot_in_closed_tree = is_root_shadow_root(parent_node)->d_func()->mode == shadow_root_mode_t::CLOSED;
            }

            // if the parent is a Window object, or the root of 'target' is a shadow including ancestor of the current
            // 'parent' (not necessarily the parent of 'target'), then append a struct to the event's path, where the
            // shadow adjusted target is nullptr, because the 'target' is attached to a tree that the 'parent' isn't
            if (dynamic_cast<nodes::window*>(parent) || is_shadow_including_ancestor(root(dynamic_cast<nodes::node*>(target)), parent_node))
            {
                activation_target = is_activation_event && !activation_target && event->d_func()->bubbles ? parent : activation_target;
                append_to_event_path(event, parent, nullptr, related_target, std::move(touch_targets), slot_in_closed_tree);
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
                append_to_event_path(event, parent, target, related_target, std::move(touch_targets), slot_in_closed_tree);
            }

            // set the 'parent_event_target' to the next parent, determined by executing the EventTarget's
            // 'get_the_parent(...)' method; do this by setting the underlying value of the pointer, as this will
            // automatically update the 'parent_node' object, which is holding a Node cast of the parent
            if (parent)
                parent = parent->d_func()->get_the_parent(event);

        } while (parent); // iterate until the parent is nullptr (parent is the related target)

        // the 'clear_targets_struct' is the last struct in the event path with a shadow adjusted target; if the target,
        // related target, or any touch targets of this struct are nodes who have ShadowRoot roots, then the target and
        // related target of the event have to be cleared once the event has finished traversing its path
        auto* clear_targets_struct = *ranges::last_where(event->d_func()->path, [](event_path_struct_t* const s) {return s->shadow_adjusted_target;});
        auto  clear_targets_list = clear_targets_struct->touch_targets + ext::vector<nodes::event_target*>{clear_targets_struct->shadow_adjusted_target, clear_targets_struct->related_target};
        clear_targets = ranges::any_of(
                clear_targets_list | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::node*>(),
                [](nodes::node* node) {return is_root_shadow_root(node);});

        // for the capturing phase, the event traverses from the top-most node (root), to the target node - the event
        // path is reversed and iterated over, invoking each listener in the capturing phase. the event phase is set to
        // AT_TARGET or CAPTURING_PHASE depending on if the current target is the final target or not
        for (auto* event_path_struct: event->d_func()->path | ranges::views::reverse)
        {
            event->d_func()->event_phase = event_path_struct->shadow_adjusted_target ? events::event::AT_TARGET : events::event::CAPTURING_PHASE;
            invoke(event_path_struct, event, events::event::CAPTURING_PHASE);
        }

        // for the bubbling phase, the event traverses from the target node to the top-most node (root), if the event
        // can bubble - the event path us iterated over, invoking each listener in the bubbling phase. the event phase
        // is set to AT_TARGET or CAPTURING_PHASE depending on if the current target is the final target or not
        for_if (event->d_func()->bubbles, auto* event_path_struct: event->d_func()->path)
        {
            event->d_func()->event_phase = event_path_struct->shadow_adjusted_target ? events::event::AT_TARGET : events::event::BUBBLING_PHASE;
            invoke(event_path_struct, event, events::event::BUBBLING_PHASE);
        }
    }

    // reset attributes of the event that relate to the current traversal of the event - the phase of the event
    // determining where in the DOM tree it currently is, the current target of the event, and the entire traversal path
    // of the event
    event->d_func()->event_phase = events::event::NONE;
    event->d_func()->current_target = nullptr;
    event->d_func()->path.clear();

    // reset the dispatch and propagation flags of the event, making the event in teh correct state to be re-emitted -
    // the dispatch flag is checked before dispatching, and the propagation flags are reset so that the event doesn't
    // unexpectedly stop straight away / after first target
    event->d_func()->dispatch_flag = false;
    event->d_func()->stop_propagation_flag = false;
    event->d_func()->stop_immediate_propagation_flag = false;

    // if the other targets are to be cleared, then set the final target and the related to nullptr, before clearing the
    // touch targets - this gives the option of maintaining the targets for re-emission, or clearing the targets for a
    // completely new purpose of the event
    if (clear_targets)
    {
        event->d_func()->target = event->d_func()->related_target = nullptr;
        event->d_func()->touch_targets.clear();
    }

    // if there is at activation target, then execute the activation behaviour of the activation target, passing the
    // event as the parameter
    if (activation_target)
        activation_target->d_func()->activation_behaviour(event);

    /* EVENT_TIMING BEGIN */
    event_timing::detail::finalize_event_timing(&entry_timing, event, target, hr_time::detail::current_hr_time(target_relevant_global_object));
    /* EVENT_TIMING END */

    // the dispatch was successful if the event wasn't cancelled during path traversal
    return !event->d_func()->canceled_flag;
}


auto dom::detail::append_to_event_path(
        events::event* const event,
        nodes::event_target* const invocation_target,
        nodes::event_target* shadow_adjusted_target,
        nodes::event_target* related_target,
        ext::vector<nodes::event_target*>&& touch_targets,
        ext::boolean  slot_in_closed_tree)
        -> void
{
    // the 'invocation_target' is in the shadow tree if it has a ShadowRoot root node, and the 'invocation_target' is
    // the root of a closed tree if it is a "closed" ShadowRoot node itself
    const ext::boolean invocation_target_in_shadow_tree = is_root_shadow_root(dynamic_cast<nodes::node*>(invocation_target));
    const ext::boolean root_of_closed_tree = dynamic_cast<nodes::shadow_root*>(invocation_target)->mode() == "closed";

    // emplace a new 'event_path_struct' into the event's path, casting the range to a vector
    event_path_struct_t s
    {
        .invocation_target = invocation_target,
        .shadow_adjusted_target = shadow_adjusted_target,
        .related_target = related_target,
        .touch_targets = std::move(touch_targets),
        .invocation_target_in_shadow_tree = invocation_target_in_shadow_tree,
        .root_of_closed_tree = root_of_closed_tree,
        .slot_in_closed_tree = slot_in_closed_tree
    };

    event->d_func()->path.emplace_back(&s);
}


auto dom::detail::invoke(
        event_path_struct_t* const s,
        events::event* const event,
        ext::number<uchar> phase)
        -> void
{
    // the viable structs are the struct in the event path that are inclusively preceding 's', and have a shadow
    // adjusted target set
    using enum ranges::views::filter_compare_t;
    auto viable_structs = ranges::subrange(event->d_func()->path.begin(), ranges::find(event->d_func()->path, s))
            | ranges::views::filter_eq<NE>(&event_path_struct_t::shadow_adjusted_target, nullptr, ext::identity{});

    // set the target to the 'viable_struct''s shadow adjusted target, and copy the related and touch targets from the
    // 's'. if the event's strop propagation flag has been set, then return early and don't invoke the callback, as the
    // event is no longer allowed to traverse the DOM tree
    event->d_func()->target = viable_structs.back()->shadow_adjusted_target;
    event->d_func()->related_target = s->related_target;
    event->d_func()->touch_targets = s->touch_targets;
    return_if(event->d_func()->stop_propagation_flag);

    // call 'inner_invoke(...)' with the event, a range copy of the event's listeners, the phase (capturing / bubbling),
    // and if the invocation target is in a shadow tree or not
    decltype(auto) listeners = event->d_func()->current_target->m_event_listeners;
    inner_invoke(event, ext::vector_view{listeners}, phase, s->invocation_target_in_shadow_tree);
}


auto dom::detail::inner_invoke(
        events::event* const event,
        ext::vector_span<ext::map<ext::string, ext::any>> event_listeners,
        ext::number<uchar> phase,
        ext::boolean  invocation_target_in_shadow_tree)
        -> void
{
    // loop through all the event listeners that have the same type as the event, and that match the capture or bubbling
    // phase of the event ie a 'capturing' listener can only be invoked for an event in the 'CAPTURING_PHASE', and a
    // listener whose 'capturing' attribute is set to false can only be invoked for an event in the 'BUBBLING_PHASE'
    for (const auto& listener: event_listeners
            | ranges::views::filter([event](const auto& listener) {return listener.at("type").template to<ext::string>() == event->d_func()->type;})
            | ranges::views::filter([phase](const auto& listener) {return listener.at("capture").template to<ext::boolean>() && phase == events::event::CAPTURING_PHASE;})
            | ranges::views::filter([phase](const auto& listener) {return !listener.at("capture").template to<ext::boolean>() && phase == events::event::BUBBLING_PHASE;}))
    {
        // if the event listener's 'once' attribute is set to true, then remove the event listener from the
        // EventTarget's listener list (not the copied range, as this won't affect the actual EventTarget)
        if (listener.at("once").to<ext::boolean>())
            event->d_func()->current_target->m_event_listeners |= ranges::actions::remove(listener);

        // type alias the callback type for convenience, and get the associated javascript realm for the listener's
        // callback function object
        auto javascript_callback = v8pp::to_v8(v8::Isolate::GetCurrent(), listener.at("callback").to<detail::event_listener_callback_t>());
        JS_REALM_GET_ASSOCIATED(javascript_callback);

        // if the global object for the associated realm is a Window object, then save its 'current_event' attribute,
        // and set the attribute to the 'event', if the invocation target is in a shadow tree TODO : why?
        events::event* current_event = nullptr;
        if (auto* global = v8pp::from_v8<nodes::window*>(javascript_callback_associated_agent, javascript_callback_associated_global_object))
        {
            current_event = global->d_func()->current_event;
            global->d_func()->current_event = invocation_target_in_shadow_tree ? event : global->d_func()->current_event;
        }

        // set the event's passive listener flag if the listener is a passive listener, invoke the callback with the
        // event type and event object, and then unset the passive listener flag in the event object, as there isn't a
        // known passive listener whose callback is currently executing
        event->d_func()->in_passive_listener_flag = listener.at("passive").to<ext::boolean>();
        listener.at("callback").to<detail::event_listener_callback_t>()("handleEvent", event);
        event->d_func()->in_passive_listener_flag = false;

        // restore the current event back to the Window associated global object
        if (auto* global = v8pp::from_v8<nodes::window*>(javascript_callback_associated_agent, javascript_callback_associated_global_object))
            global->d_func()->current_event = current_event;

        // return if the stop immediate propagation flag is set, as this disallows any more listeners from being called
        // on the event, even if they are on the same target
        return_if(event->d_func()->stop_immediate_propagation_flag);
    }
}


template <ext::inherit<dom::events::event> T>
auto dom::detail::fire_event(
        ext::string&& e,
        nodes::event_target* target,
        ext::map<ext::string, ext::any>&& init)
        -> ext::boolean
{
    using namespace std::string_literals;

    string_switch(e)
    {
        string_case("pointerover"):
        string_case("pointerdown"):
        string_case("pointermove"):
        string_case("pointerup"):
        string_case("pointerout"):
            init.template insert_or_assign("bubbles", true);
            init.template insert_or_assign("cancelable", true);
            break;

        string_case("pointerenter"):
        string_case("pointerleave"):
        string_case("load"):
        string_case("unload"):
        string_case("abort"):
        string_case("error"):
            init.template insert_or_assign("bubbles", false);
            init.template insert_or_assign("cancelable", false);
            break;

        string_case("pointerrawupdate"):
        string_case("pointercancel"):
        string_case("gotpointercapture"):
        string_case("lostpointercapture"):
        string_case("select"):
        string_case("animationstart"):
        string_case("animationend"):
        string_case("animationiteration"):
        string_case("animationcancelable"):
            init.template insert_or_assign("bubbles", true);
            init.template insert_or_assign("cancelable", false);
            break;

        string_case("touchcancel"):
            init.template insert_or_assign("cancelable", false);
            init.template insert_or_assign("bubbles", true);
            init.template insert_or_assign("composed", true);
            break;

        string_case("blur"):
        string_case("focus"):
        string_case("mouseenter"):
        string_case("mouseleave"):
            init.template insert_or_assign("bubbles", false);
            init.template insert_or_assign("cancelable", false);
            init.template insert_or_assign("composed", true);
            break;

        string_case("focusin"):
        string_case("focusout"):
        string_case("input"):
        string_case("compositionupdate"):
        string_case("compositionend"):
            init.template insert_or_assign("bubbles", true);
            init.template insert_or_assign("cancelable", false);
            init.template insert_or_assign("composed", true);
            break;

        string_case("auxclick"):
        string_case("click"):
        string_case("contextmenu"):
        string_case("dblclick"):
        string_case("mousedown"):
        string_case("mousemove"):
        string_case("mouseout"):
        string_case("mouseover"):
        string_case("mouseup"):
        string_case("beforeinput"):
        string_case("keydown"):
        string_case("keyup"):
        string_case("compositionstart"):
            init.template insert_or_assign("bubbles", true);
            init.template insert_or_assign("cancelable", true);
            init.template insert_or_assign("composed", true);
            break;

        string_case("wheel"):
        string_case("touchstart"):
        string_case("touchend"):
        string_case("touchmove"):
            init.template insert_or_assign("bubbles", true);
            init.template insert_or_assign("composed", true);
            break;
    }

    if constexpr (type_is<T, indexed_db::events::idb_version_change_event>)
    {
        init.template insert_or_assign("bubbles", false);
        init.template insert_or_assign("cancelable", false);
    }

    // create a new event of type T, setting the event type and options, and then dispatch it to 'target'
    T event {std::move(e), std::move(init)};
    return dispatch(&event, target);
}
