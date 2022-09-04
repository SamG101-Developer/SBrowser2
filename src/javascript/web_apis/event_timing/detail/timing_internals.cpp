#include "timing_internals.hpp"

#include "dom/events/event.hpp"

#include <range/v3/algorithm/contains.hpp>


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
            "compositionupdate", "compositionend", "dragstart", "dragend", "dragenter", "dragleave", "dragover", "drop"};

    // If the event type is in the list of allowed event types, then the event should be considered for event timing --
    // the event is can be times, for example a click or key press.
    return ranges::contains(allowed_event_types, event->type());
}
