module;
#include <range/v3/view/transform.hpp>
#include <v8pp/convert.hpp>


module apis.dom.event_private;
import apis.dom.window;
import apis.dom.event_target;
import apis.dom.types;
import ext.core;
import js.env.realms;


auto dom::event_private::dispatch(
        event_target* target)
        -> ext::boolean
{
    ACCESS_QIMPL;
    dispatch_flag = true;

    /* ↓ [LARGEST-CONTENTFUL-PAINT] ↓ */
    auto e = js::env::env::relevant(target);
    if (auto* window = e.cpp.global<window*>(); window != nullptr && type == u"scroll" && is_trusted)
        window->d_func()->has_dispatched_scroll_event = true;
    /* ↑ [LARGEST-CONTENTFUL-PAINT] ↑ */

    /* ↓ [EVENT-TIMING] ↓ */
    auto interaction_id = event_timing::detail::compute_interaction_id(q);
    auto entry_timing = event_timing::detail::initialize_event_timing(q, hr_time::detail::current_hr_time(e.js.global()), std::move(interaction_id));
    /* ↑ [EVENT-TIMING] ↑ */

    decltype(auto) is_activation_event = type == u"click" && dom_cast<ui_events::events::mouse_event*>(event)
    decltype(auto) activation_target = is_activation_event ? target : nullptr;
    decltype(auto) related_target = detail::retarget(event->d_func()->related_target, target);
    auto clear_targets = ext::boolean::FALSE_();

    if (target != related_target || target == event->d_func()->related_target)
    {
        // The current parent is the target (make the 1 loop, rather than have initialization scripts and then the loop
        // after with variables changing i.e. roll the unrolled single execution for target by merging it with the
        // parent script).
        decltype(auto) parent = target;

        do
        {
            // The 'related_target' is the event's related target, transformed to be retargeted against the current
            // 'parent'. TODO : Why retarget
            related_target = retarget(event->d_func()->related_target, parent);

            // The 'slot_in_closed_tree' always defaults to false, and can be changed if the 'parent' is an assigned
            // slottable. The 'touch_targets' are the event's touch targets, transformed to be retargeted against the
            // current parent.
            auto slot_in_closed_tree = ext::boolean::FALSE_();
            auto touch_targets = event->d_func()->touch_targets | ranges::views::transform(BIND_BACK(retarget, parent));

            // If the 'parent' is assigned (and implicitly therefore a slottable), then assert that the parent is a slot
            // too. The slot is in a closed tree if the mode of the ShadowRoot is "closed" TODO : why
            if (is_assigned(parent_node))
            {
                ASSERT(is_slot(parent_node));
                slot_in_closed_tree = is_root_shadow_root(parent_node)->d_func()->mode == shadow_root_mode_t::CLOSED;
            }

            // If the 'parent' is a Window object, or the root of 'target' is a shadow-including-ancestor of the current
            // 'parent' (not necessarily the parent of 'target'), then append a struct to the event's path, where the
            // shadow adjusted target is nullptr, because the 'target' is attached to a tree that the 'parent' isn't.
            if (dom_cast<nodes::window*>(parent) || is_shadow_including_ancestor(root(dynamic_cast<dom::node*>(target)), parent))
            {
                activation_target = is_activation_event && !activation_target && event->d_func()->bubbles ? parent : activation_target;
                append_to_event_path(event, parent, nullptr, related_target, std::move(touch_targets), slot_in_closed_tree);
            }

                // If the 'parent' is the 'related_target', then set the 'parent', and its Node cast to nullptr; this will
                // stop the 'get_the_parent(...)' algorithm being called, meaning that the loop will terminate (guard
                // condition to the do-while checks that a parent exists for next iteration)
            else if (parent == related_target)
                parent = nullptr;

                // Otherwise, a struct with the shadow adjusted target set to the target' is appended to the Event's path;
                // the TODO : shadows.
            else
            {
                activation_target = is_activation_event && !activation_target ? target : activation_target;
                append_to_event_path(event, parent, target, related_target, std::move(touch_targets), slot_in_closed_tree);
            }

            // Set the 'parent_event_target' to the next parent, determined by executing the EventTarget's
            // 'get_the_parent(...)' method; do this by setting the underlying value of the pointer, as this will
            // automatically update the 'parent_node' object, which is holding a Node cast of the parent.
            if (parent)
                parent = parent->d_func()->get_the_parent(event);

        } while (parent); // iterate until the parent is nullptr (parent is the related target)

        // The 'clear_targets_struct' is the last struct in the event path with a shadow adjusted target; if the target,
        // related target, or any touch targets of this struct are nodes who have ShadowRoot roots, then the target and
        // related target of the event have to be cleared once the event has finished traversing its path.
        auto* clear_targets_struct = *ranges::last_where(event->d_func()->path, [](event_path_struct_t* const s) {return s->shadow_adjusted_target;});
        auto  clear_targets_list = clear_targets_struct->touch_targets + ext::vector<nodes::event_target*>{clear_targets_struct->shadow_adjusted_target, clear_targets_struct->related_target};
        clear_targets = ranges::any_of(
                clear_targets_list | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::node*>(),
                [](nodes::node* node) {return is_root_shadow_root(node);});

        // For the capturing phase, the event traverses from the top-most node (root), to the target node - the event
        // path is reversed and iterated over, invoking each listener in the capturing phase. the event phase is set to
        // AT_TARGET or CAPTURING_PHASE depending on if the current target is the final target or not.
        for (auto* event_path_struct: event->d_func()->path | ranges::views::reverse)
        {
            event->d_func()->event_phase = event_path_struct->shadow_adjusted_target ? events::event::AT_TARGET : events::event::CAPTURING_PHASE;
            invoke(event_path_struct, event, events::event::CAPTURING_PHASE);
        }

        // For the bubbling phase, the event traverses from the target node to the top-most node (root), if the event
        // can bubble - the event path us iterated over, invoking each listener in the bubbling phase. the event phase
        // is set to AT_TARGET or CAPTURING_PHASE depending on if the current target is the final target or not.
        for_if (event->d_func()->bubbles, auto* event_path_struct: event->d_func()->path)
        {
            event->d_func()->event_phase = event_path_struct->shadow_adjusted_target ? events::event::AT_TARGET : events::event::BUBBLING_PHASE;
            invoke(event_path_struct, event, events::event::BUBBLING_PHASE);
        }
    }

    // Reset attributes of the event that relate to the current traversal of the event - the phase of the event
    // determining where in the DOM tree it currently is, the current target of the event, and the entire traversal path
    // of the event.
    event_phase = events::event::NONE;
    current_target = nullptr;
    path.clear();

    // Reset the dispatch and propagation flags of the event, making the event in teh correct state to be re-emitted -
    // the dispatch flag is checked before dispatching, and the propagation flags are reset so that the event doesn't
    // unexpectedly stop straight away / after first target.
    dispatch_flag = false;
    stop_propagation_flag = false;
    stop_immediate_propagation_flag = false;

    // If the other targets are to be cleared, then set the final target and the related to nullptr, before clearing the
    // touch targets - this gives the option of maintaining the targets for re-emission, or clearing the targets for a
    // completely new purpose of the event.
    if (clear_targets)
    {
        target = event->d_func()->related_target = nullptr;
        touch_targets.clear();
    }

    // If there is at activation target, then execute the activation behaviour of the activation target, passing the
    // event as the parameter.
    if (activation_target)
        activation_target->d_func()->activation_behaviour(event);

    /* ↓ [EVENT-TIMING] ↓ */
    event_timing::detail::finalize_event_timing(&entry_timing, event, target, hr_time::detail::current_hr_time(target_relevant_global_object));
    /* ↑ [EVENT-TIMING] ↑ */

    // The dispatch was successful if the event wasn't cancelled during path traversal.
    return !event->d_func()->canceled_flag;
}


auto dom::event_private::append_to_event_path(
        nodes::event_target* invocation_target,
        nodes::event_target* shadow_adjusted_target,
        nodes::event_target* related_target,
        ext::vector<nodes::event_target*>&& touch_targets,
        ext::boolean  slot_in_closed_tree)
        -> void
{
    // The 'invocation_target' is in the shadow tree if it has a ShadowRoot root node, and the 'invocation_target' is
    // the root of a closed tree if it is a "closed" ShadowRoot node itself.
    const ext::boolean invocation_target_in_shadow_tree = is_root_shadow_root(dynamic_cast<nodes::node*>(invocation_target));
    const ext::boolean root_of_closed_tree = dynamic_cast<nodes::shadow_root*>(invocation_target)->mode() == u"closed";

    // Emplace a new 'event_path_struct' into the event's path (create the unique_ptr<event_path_struct_t>, and move it
    // into the event's path.
    auto s = std::make_unique<event_path_struct_t>();
    s->invocation_target = invocation_target;
    s->shadow_adjusted_target = shadow_adjusted_target;
    s->related_target = related_target;
    s->touch_targets = std::move(touch_targets);
    s->invocation_target_in_shadow_tree = invocation_target_in_shadow_tree;
    s->root_of_closed_tree = root_of_closed_tree;
    s->slot_in_closed_tree = slot_in_closed_tree;

    event->d_func()->path.emplace_back(std::move(s));
}


auto dom::event_private::invoke(
        event_path_struct_t& s,
        ext::number<uchar> phase)
        -> void
{
    // The viable structs are the structs in the event's path that are inclusively preceding 's', and have a shadow
    // adjusted target set (non-nullptr).
    using enum ranges::views::filter_compare_t;
    auto viable_structs = ranges::subrange(event->d_func()->path.begin(), ranges::find(event->d_func()->path, s), ext::deref)
            | ranges::views::filter_eq<NE>(&event_path_struct_t::shadow_adjusted_target, nullptr, ext::identity{});

    // Set the target to the 'viable_struct''s shadow adjusted target, and copy the related and touch targets from the
    // 's'. if the event's stop propagation flag has been set, then return early and don't invoke the callback, as the
    // event is no longer allowed to traverse the DOM tree.
    event->d_func()->target = viable_structs.back()->shadow_adjusted_target;
    event->d_func()->related_target = s->related_target;
    event->d_func()->touch_targets = s->touch_targets;
    return_if(event->d_func()->stop_propagation_flag);

    // Call 'inner_invoke(...)' with the event, a range copy of the event's listeners, the phase (capturing / bubbling),
    // and if the invocation target is in a shadow tree or not.
    decltype(auto) listeners = event->d_func()->current_target->m_event_listeners;
    inner_invoke(event, ext::vector_view{listeners}, phase, s->invocation_target_in_shadow_tree);
}


auto dom::event_private::inner_invoke(
        ext::vector_span<ext::map<ext::string, ext::any>> event_listeners,
        ext::number<uchar> phase,
        ext::boolean  invocation_target_in_shadow_tree)
        -> void
{
    // Loop through all the event listeners that have the same type as the event, and that match the capture or bubbling
    // phase of the event ie a 'capturing' listener can only be invoked for an event in the 'CAPTURING_PHASE', and a
    // listener whose 'capturing' attribute is set to false can only be invoked for an event in the 'BUBBLING_PHASE'.
    for (const auto& listener: event_listeners
            | ranges::views::filter([event](const auto& listener) {return listener.at(u"type").template to<ext::string>() == event->d_func()->type;})
            | ranges::views::filter([phase](const auto& listener) {return listener.at(u"capture").template to<ext::boolean>() && phase == events::event::CAPTURING_PHASE;})
            | ranges::views::filter([phase](const auto& listener) {return !listener.at(u"capture").template to<ext::boolean>() && phase == events::event::BUBBLING_PHASE;}))
    {
        // If the event listener's 'once' attribute is set to true, then remove the event listener from the
        // EventTarget's listener list (not the copied range, as this won't affect the actual EventTarget).
        if (listener.at("once").to<ext::boolean>())
            event->d_func()->current_target->m_event_listeners |= ranges::actions::remove(listener);

        // Type alias the callback type for convenience, and get the associated javascript realm for the listener's
        // callback function object.
        auto javascript_callback = v8pp::to_v8(v8::Isolate::GetCurrent(), listener.at(u"callback").to<detail::event_listener_callback_t>());
        auto e = js::env::env::associated(javascript_callback);

        // If the global object for the associated realm is a Window object, then save its 'current_event' attribute,
        // and set the attribute to the 'event', if the invocation target is in a shadow tree TODO : why?.
        events::event* current_event = nullptr;
        if (auto* global = v8pp::from_v8<nodes::window*>(javascript_callback_associated_agent, javascript_callback_associated_global_object))
        {
            current_event = global->d_func()->current_event;
            global->d_func()->current_event = invocation_target_in_shadow_tree ? event : global->d_func()->current_event;
        }

        // Set the event's passive listener flag if the listener is a passive listener, invoke the callback with the
        // event type and event object, and then unset the passive listener flag in the event object, as there isn't a
        // known passive listener whose callback is currently executing.
        event->d_func()->in_passive_listener_flag = listener.at(u"passive").to<ext::boolean>();
        listener.at(u"callback").to<detail::event_listener_callback_t>()(u"handleEvent", event);
        event->d_func()->in_passive_listener_flag = false;

        // Restore the current event back to the Window associated global object.
        if (auto* global = v8pp::from_v8<nodes::window*>(javascript_callback_associated_agent, javascript_callback_associated_global_object))
            global->d_func()->current_event = current_event;

        // Return if the stop immediate propagation flag is set, as this disallows any more listeners from being called
        // on the event, even if they are on the same target.
        return_if(event->d_func()->stop_immediate_propagation_flag);
    }
}

