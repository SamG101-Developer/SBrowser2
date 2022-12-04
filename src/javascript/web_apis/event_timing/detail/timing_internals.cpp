#include "timing_internals.hpp"


#include "ext/hashing.ixx"
#include "ext/assertion.hpp"


#include "javascript/environment/realms.hpp"

#include "dom/events/event.hpp"
#include "dom/events/event_private.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "event_timing/event_counts.hpp"
#include "event_timing/event_counts_private.hpp"
#include "event_timing/performance_event_timing.hpp"
#include "event_timing/performance_event_timing_private.hpp"

#include "hr_time/performance.hpp"
#include "performance_timeline/detail/processing_internals.hpp"
#include "pointer_events/pointer_event.hpp"
#include "pointer_events/pointer_event_private.hpp"

#include "ui_events/input_event.hpp"
#include "ui_events/keyboard_event.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <v8pp/convert.hpp>


auto event_timing::detail::should_event_be_considered_for_event_timing(
        dom::events::event* event)
        -> ext::boolean
{
    // If an event isn't trusted, then the event should NOT be considered for event timing (only secure events are
    // permitted)
    return_if (!event->d_func()->is_trusted) false;

    // Create a list of allowed event types
    auto allowed_event_types = {
            u"auxclick", u"click", u"contextmenu", u"dblclick", u"mousedown", u"mouseenter", u"mouseleave", u"mouseout",
            u"mouseover", u"mouseup", u"pointerover", u"pointerenter", u"pointerdown", u"pointerup", u"pointercancel",
            u"pointerout", u"pointerleave", u"gotpointercapture", u"lostpointercapture", u"touchstart", u"touchend",
            u"touchcancel", u"keydown", u"keypress", u"keyup", u"beforeinput", u"input", u"compositionstart",
            u"compositionupdate", u"compositionend", u"dragstart", u"dragend", u"dragenter", u"dragleave", u"dragover",
            u"drop"};

    // If the event type is in the list of allowed event types, then the event should be considered for event timing --
    // the event is can be times, for example a click or key press.
    return ranges::contains(allowed_event_types, event->d_func()->type);
}


auto event_timing::detail::should_add_performance_event_timing(
        performance_event_timing* entry,
        detail::performance_observer_init_t&& options)
        -> ext::boolean
{
    // If the 'entry's 'entry_type' is "first-input", then the PerformanceEventTiming should automatically be added, as
    // it isn't being used for anything else / doesn't require any other configurations. Otherwise, assert that the
    // 'entry_type' is "event", and continue.
    return_if (entry->d_func()->entry_type == u"first-input") true;
    ASSERT(entry->d_func()->entry_type == u"event",
           entry->d_func()->entry_type);

    // The 'min_duration' is the maximum of the given "durationThreshold" from the options against 16, otherwise the
    // numeric value 104. Return if the 'entry's 'duration' is greater than the 'min_duration' -- TODO: Why?
    auto min_duration = options.contains(u"durationThreshold") ? ext::max(options[u"durationThreshold"].to<ext::number<int>>(), 16) : 104;
    return entry->d_func()->duration > min_duration;
}


auto event_timing::detail::increase_interaction_count(
        dom::nodes::window* window,
        ext::string&& type)
        -> void
{
    // Increment the number of user interactions with the Window by 1 (can be any small number), and then assert that
    // the type exists in the Window object's interaction counts map, because this element in the map needs to be
    // incremented.
    window->d_func()->user_interaction_value += 1;
    ASSERT(window->d_func()->interaction_counts.contains(type));

    // Increment the number on interactions for 'type' in the Window object's interaction count map.
    window->d_func()->interaction_counts[std::move(type)] += 1;
}


auto event_timing::detail::compute_interaction_id(
        dom::events::event* event)
        -> ext::number<int>
{
    // If an event isn't trusted, then the event should NOT be considered for event timing (only secure events are
    // permitted)
    return_if (!event->d_func()->is_trusted) 0;

    // If the event type is not in the list of allowed event types, then the event cannot have an interaction id
    // computed, so return 0 (sort of invalid default)
    auto allowed_event_types = {"keyup", "compositionstart", "input", "pointercancel", "pointermove", "pointerup", "click"};
    return_if (ranges::contains(allowed_event_types, event->d_func()->type)) 0;

    // Get the relevant Window global object
    auto e = js::env::env::relevant(event);
    decltype(auto) window = e.cpp.global<dom::nodes::window*>();

    // Cast the event to the 3 different event types it can be
    decltype(auto) key_event = dynamic_cast<ui_events::keyboard_event*>(event);
    decltype(auto) input_event = dynamic_cast<ui_events::input_event*>(event);
    decltype(auto) pointer_event = dynamic_cast<pointer_events::pointer_event*>(event);

    string_switch(event->d_func()->type)
    {
        string_case(u"keyup"):
            // If the KeyboardEvent is composing, or the KeyboardEvent's key code isn't pending down in the Window, then
            // return 0 -- the non-composing key code must be in the windows 'm_pending_key_downs'. Otherwise, increase
            // the interaction count for the window and "keyboard", as a valid keyboard interaction is occurring.
            return_if (key_event->d_func()->is_composing) 0;
            return_if (!window->d_func()->pending_key_downs.contains(key_event->d_func()->code)) 0;
            increase_interaction_count(window, u"keyboard");

            // Set the interaction id for the Window's 'm_pending_key_down' entry for the KeyboardEvent's key code to
            // the Window's 'm_user_interaction_value', because the key is being interacted with by the Window. Push
            // this entry into the Window's 'm_entries_to_be_queued', and then remove the key code from the Windows
            // 'm_pending_key_downs', because the key is no longer pending -- execution has finished.
            window->d_func()->pending_key_downs[key_event->code]->interaction_id = window->d_func()->user_interaction_value;
            window->d_func()->entries_to_be_queued.push_back(window->d_func()->pending_key_downs[key_event->code]);
            window->d_func()->pending_key_downs |= ranges::actions::remove(key_event->code);
            return window->d_func()->user_interaction_value;

        string_case(u"comopositionstart"):
            // For the "compositionstart" event, queue every entry in the Window's 'm_pending_key_downs' in order, and
            // then clear all the entries from the Window's 'm_pending_key_downs'. Return 0; TODO: Why?
            ranges::for_each(window->d_func()->pending_key_downs, window->d_func()->entries_to_be_queued.push_back);
            window->d_func()->pending_key_downs.clear();
            return 0;

        string_case(u"input"):
            // Input event's can be of the Event or InputEvent interface, and as this only to applies to InputEvent
            // interfaces, return 0 if the interface is Event, or if the event 'is_composing'. Otherwise, increase the
            // interaction count for the window and "keyboard", as a valid keyboard interaction is occurring.
            return_if (!input_event) 0;
            return_if (!input_event->d_func()->is_composing) 0;
            increase_interaction_count(window, u"keyboard");

            // Return the Window's 'm_user_interaction_value' as the interaction id. TODO: Why?
            return window->d_func()->user_interaction_value;

        string_default:
            // Alias the PointerEvent's 'pointer_id'
            decltype(auto) pointer_id = pointer_event->d_func()->pointer_id;

            // If the event's type is "click"
            if (event->d_func()->type == u"click")
            {
                // If the 'pointer_id' isn't contained in the Window's 'm_pointer_interaction_value_map', then return 0,
                // because the value at this entry in the amp is required for further processing.
                return_if (!window->d_func()->pointer_interaction_value_map.contains(pointer_id)) 0;

                // Alias the corresponding value of the Window's 'm_pointer_interaction_value_map's entry at
                // 'pointer_id', defaulting to nullptr. Remove the 'pointer_id' from the Window's
                // 'm_pointer_interaction_value_map' and 'm_pointer_is_drag_set' (execution has finished for
                // 'pointer_id'). Return the value (it was associated with the 'pointer_id' in the Window)
                decltype(auto) value = window->d_func()->pointer_interaction_value_map[pointer_id];
                window->d_func()->pointer_interaction_value_map |= ranges::actions::remove(pointer_id);
                window->d_func()->pointer_is_drag_set |= ranges::actions::remove(pointer_id);
                return value;
            }

            // If the event's type is "pointermove"
            else if (event->d_func()->type == u"pointermove")
            {
                // Add the 'pointer_id' into the Window's 'm_pointer_is_drag_set', because the pointer is currently
                // moving. Return 0. TODO: Why?
                window->d_func()->pointer_is_drag_set.emplace(pointer_id);
                return 0;
            }

            // Assert tht the event's type is "pointerup" or "pointercancel", because these are the only other types of
            // events that are allowed (for this method).
            ASSERT(pointer_event->d_func()->type == u"pointerup" || pointer_event->d_func()->type == u"pointercancel", pointer_event->d_func()->type);

            // If there is no value at the 'pointer_id' entry, then return the default 0. Otherwise, assert that the
            // value can be cast to the PeformanceEventTiming object.
            return_if (!window->d_func()->pending_pointer_downs.contains(pointer_id)) 0;
            ASSERT(dom_cast<performance_event_timing*>(window->d_func()->pending_pointer_downs[pointer_id]));

            // If the event's type is "pointerup"
            if (pointer_event->d_func()->type == u"pointerup")
            {
                // Get the interaction type: "drag" if the 'pointer_id' is in the Window's 'm_pointer_is_drag_set',
                // otherwise "tap". Increase the interaction count for the window and the 'interaction_type'.
                auto interaction_type = window->d_func()->pointer_is_drag_set.contains(pointer_id) ? u"drag" : u"tap";
                increase_interaction_count(window, interaction_type);

                // Set the interaction value for the pointer to the Window's 'm_user_interaction_value', and update the
                // Window's interaction id of the entry in the Window's 'm_pending_pointer_downs' to the same value.
                window->d_func()->pointer_interaction_value_map[pointer_id] = window->d_func()->user_interaction_value;
                window->d_func()->pending_pointer_downs[pointer_id]->interaction_id = window->d_func()->user_interaction_value;
            }

            // Push the PerformanceEventTiming object associated with the 'pointer_id' in the Window's
            // 'm_pending_pointer_downs' map. Remove the 'pointer_id' from the Window's 'm_pending_pointer_down's, as
            // the pointer is no longer pending. Return 0 if the event's type is "pointercancel", otherwise the
            // interaction id associated with the 'pointer_id' in the Window's 'm_pointer_interaction_value_map'.
            window->d_func()->entries_to_be_queued.push_back(window->d_func()->pending_pointer_downs[pointer_id]);
            window->d_func()->pending_pointer_downs |= ranges::actions::remove(pointer_id);
            return pointer_event->d_func()->type == "pointercancel" ? 0 : window->d_func()->pointer_interaction_value_map[pointer_id];
    }
}


auto event_timing::detail::initialize_event_timing(
        dom::events::event* event,
        ext::number<double> processing_start,
        ext::number<int> interaction_id)
        -> std::unique_ptr<performance_event_timing>
{
    // Create a PerformanceEventTiming object, and assign the attributes to it based on the parameters and attributes of
    // the parameters passed into the function. Return the object created.
    auto timing_entry = std::make_unique<performance_event_timing>();
    timing_entry->d_func()->name = event->d_func()->type;
    timing_entry->d_func()->entry_type = u"event";
    timing_entry->d_func()->start_time = event->d_func()->time_stamp;
    timing_entry->d_func()->processing_start = processing_start;
    timing_entry->d_func()->cancelable = event->d_func()->cancelable;
    timing_entry->d_func()->interaction_id = interaction_id;
    return timing_entry;
}


auto event_timing::detail::finalize_event_timing(
        performance_event_timing* timing_entry,
        dom::events::event* event,
        dom::nodes::event_target* target,
        ext::number<double> processing_end)
        -> void
{
    auto e = js::env::env::relevant(target);

    // Return if the 'timing_entry' is a nullptr, or if the global object isn't a Window, because properties of the
    // Window are required to use in the method.
    return_if (!timing_entry);
    return_if (!e.cpp.global<dom::nodes::window*>());

    // Set the 'timing_entry's to the 'processing_end', and assert that the target implements the Node class (if the
    // assert fails, then the rest of the method doesn't execute, but the processing end time is still set).
    timing_entry->d_func()->processing_end = processing_end;
    ASSERT(dom_cast<dom::nodes::node*>(target));

    // Get the global object as a Window, and set the 'timing_entry's target to the element generated from the
    // element-timing API's get_element(...) detail method.
    decltype(auto) window = e.cpp.global<dom::nodes::window*>();
    timing_entry->d_func()->target = element_timing::deail::get_element(target, window->d_func()->document.get());

    if (timing_entry->d_func()->name != u"keydown" || timing_entry->d_func()->name != u"pointerdown")
        window->d_func()->entries_to_be_queued.push_back(timing_entry);

    if (timing_entry->d_func()->name == u"pointerdown")
    {
        decltype(auto) pointer_event = dynamic_cast<pointer_events::pointer_event*>(event);
        decltype(auto) pointer_id = pointer_event->d_func()->pointer_id;

        if (window->d_func()->pending_pointer_downs.contains(pointer_id))
            window->d_func()->entries_to_be_queued.push_back(window->d_func()->pending_pointer_downs[pointer_id]);
        window->d_func()->pending_pointer_downs[pointer_id] = timing_entry;
    }

    else if (timing_entry->d_func()->name == u"keydown")
    {
        decltype(auto) key_event = dynamic_cast<ui_events::keyboard_event*>(event);

        return_if (key_event->is_composing()) window->d_func()->entries_to_be_queued.push_back(timing_entry);

        if (window->d_func()->pending_key_downs.contains(key_event->d_func()->code))
        {
            auto entry = window->d_func()->pending_key_downs[key_event->d_func()->code];
            if (key_event->d_func()->code != 229)
            {
                window->d_func()->user_interaction_value += 1;
                entry->interaction_id = window->d_func()->user_interaction_value;
            }

            window->d_func()->entries_to_be_queued.push_back(entry);
            window->d_func()->pending_key_downs |= ranges::actions::remove(key_event->d_func()->code);
        }

        window->d_func()->pending_key_downs[key_event->d_func()->code] = timing_entry;
    }
}


auto event_timing::detail::dispatch_pending_event_timing_entries(
        dom::nodes::document* document)
        -> void
{
    auto e = js::env::env::relevant(document);
    decltype(auto) window = e.cpp.global<dom::nodes::window*>();
    auto rendering_timestamp = hr_time::detail::current_hr_time(e.js.global());

    for (const auto& timing_entry: window->d_func()->entries_to_be_queued)
    {
        set_event_timing_entry_duration(timing_entry, window, rendering_timestamp);
        if (timing_entry->d_func()->duration > 16) performance_timeline::detail::queue_performance_entry(timing_entry);
    }

    window->d_func()->entries_to_be_queued.clear();
    for (decltype(auto) pending_down: window->d_func()->pending_pointer_downs)
        set_event_timing_entry_duration(pending_down, window, rendering_timestamp);
}


auto event_timing::detail::set_event_timing_entry_duration(
        performance_event_timing* timing_entry,
        dom::nodes::window* window,
        hr_time::dom_high_res_time_stamp rendering_timestamp)
        -> void
{
    return_if (timing_entry->d_func()->duration != 0);

    auto start = timing_entry->d_func()->start_time;
    auto name  = timing_entry->d_func()->name;
    timing_entry->d_func()->duration = (rendering_timestamp - start) + ext::random::get(-8, 8);

    ASSERT(window->d_func()->event_counts->d_func()->map->contains(name));
    window->d_func()->event_counts[std::move(name)] += 1;

    return_if (window->d_func()->has_dispatched_input_event);

    if (name == u"pointerdown")
    {
        window->d_func()->pending_first_pointer_down.reset(auto{timing_entry});
        window->d_func()->pending_first_pointer_down->d_func()->entry_type = u"first-input";
    }

    else if (name == u"pointerup" && window->d_func()->pending_first_pointer_down)
    {
        window->d_func()->has_dispatched_input_event = true;
        performance_timeline::detail::queue_performance_entry(window->d_func()->pending_first_pointer_down.get());
    }

    else if (name == u"click" || name == u"keydown" || name == u"mousedown")
    {
        window->d_func()->has_dispatched_input_event = true;
        auto new_first_input_delay_entry = auto{timing_entry};
        new_first_input_delay_entry->d_func()->entry_type = u"first-input";
        performance_timeline::detail::queue_performance_entry(new_first_input_delay_entry);
    }
}
