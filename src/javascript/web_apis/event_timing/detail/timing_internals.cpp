#include "timing_internals.hpp"

#include "ext/type_traits.hpp"
#include "ext/assertion.hpp"
#include "ext/string.hpp"

#include "dom/events/event.hpp"
#include "dom/nodes/window.hpp"

#include "event_timing/performance_event_timing.hpp"
#include "ui_events/keyboard_event.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <v8pp/convert.hpp>


auto event_timing::detail::should_event_be_considered_for_event_timing(
        dom::events::event* event)
        -> ext::boolean
{
    // If an event isn't trusted, then the event should NOT be considered for event timing (only secure events are
    // permitted)
    return_if (!event->is_trusted()) false;

    // Create a list of allowed event types
    auto allowed_event_types = {
            "auxclick", "click", "contextmenu", "dblclick", "mousedown", "mouseenter", "mouseleave", "mouseout",
            "mouseover", "mouseup", "pointerover", "pointerenter", "pointerdown", "pointerup", "pointercancel",
            "pointerout", "pointerleave", "gotpointercapture", "lostpointercapture", "touchstart", "touchend",
            "touchcancel", "keydown", "keypress", "keyup", "beforeinput", "input", "compositionstart",
            "compositionupdate", "compositionend", "dragstart", "dragend", "dragenter", "dragleave", "dragover",
            "drop"};

    // If the event type is in the list of allowed event types, then the event should be considered for event timing --
    // the event is can be times, for example a click or key press.
    return ranges::contains(
            allowed_event_types,
            event->type());
}


auto event_timing::detail::should_add_performance_event_timing(
        performance_event_timing* entry,
        detail::performance_observer_init_t&& options)
        -> ext::boolean
{
    // If the 'entry's 'entry_type' is "first-input", then the PerformanceEventTiming should automatically be added, as
    // it isn't being used for anything else / doesn't require any other configurations. Otherwise, assert that the
    // 'entry_type' is "event", and continue.
    return_if (entry->entry_type() == "first-input") true;
    ASSERT(entry->entry_type() == "event",
           entry->entry_type());

    // The 'min_duration' is the maximum of the given "durationThreshold" from the options against 16, otherwise the
    // numeric value 104. Return if the 'entry's 'duration' is greater than the 'min_duration' -- TODO: Why?
    auto min_duration = options.contains("durationThreshold") ? ext::max(options["durationThreshold"].to<ext::number<int>>(), 16) : 104;
    return entry->duration() > min_duration;
}


auto event_timing::detail::increase_interaction_count(
        dom::nodes::window* window,
        ext::string&& type)
        -> void
{
    // Increment the number of user interactions with the Window by 1 (can be any small number), and then assert that
    // the type exists in the Window object's interaction counts map, because this element in the map needs to be
    // incremented.
    window->m_user_interaction_value += 1;
    ASSERT(window->m_interaction_counts.contains(type));

    // Increment the number on interactions for 'type' in the Window object's interaction count map.
    window->m_interaction_counts[std::move(type)] += 1;
}


auto event_timing::detail::compute_interaction_id(
        dom::events::event* event)
        -> ext::string
{
    using namespace std::string_literals;
    return_if (!event->is_trusted()) "0";

    auto allowed_event_types = {"keyup", "compositionstart", "input", "pointercancel", "pointermove", "pointerup", "click"};
    return_if (ranges::contains(allowed_event_types, event->type())) "0";

    JS_REALM_GET_RELEVANT(event);
    decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(event_relevant_agent, event_relevant_global_object);

    string_switch(event->type())
    {
        string_case(ext::string{"keyup"})
            decltype(auto) key_event = dynamic_cast<ui_events::key_event*>(event);
            return_if (key_event->is_composing()) "0";
            return_if (!window->m_pending_key_downs.contains(key_event->key_code())) "0";
    }
}
