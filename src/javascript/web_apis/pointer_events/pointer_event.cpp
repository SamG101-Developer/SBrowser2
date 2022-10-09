#include "pointer_event.hpp"
#include "pointer_event_private.hpp"

#include "dom/nodes/event_target.hpp"

#include <range/v3/view/concat.hpp>
#include <range/v3/view/single.hpp>
#include <range/v3/view/transform.hpp>


pointer_events::pointer_event::pointer_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_events::mouse_event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(pointer_event);
    ACCESS_PIMPL(pointer_event);

    d->pointer_id = 0;
    d->width = 1.0;
    d->height = 1.0;
    d->pressure = 0.0f;
    d->tangential_pressure = 0.0f;
    d->tilt_x = 0;
    d->tilt_y = 0;
    d->twist = 0;
    d->altitude_angle = 0.0;
    d->azimuth_angle = 0.0;
    d->pointer_type = u8"";
    d->is_primary = false;

    d->coalesced_events = event_init[u8"coalescedEvents"].to<decltype(d->coalesced_events)>();
    d->predicted_events = event_init[u8"predictedEvents"].to<decltype(d->coalesced_events)>();

    for_if (d->is_trusted, auto* event: ranges::views::concat(d->coalesced_events, d->predicted_events))
    {
        // inherit these properties from his PointerEvent
        event->d_func()->pointer_id = d->pointer_id;
        event->d_func()->pointer_type = d->pointer_type;
        event->d_func()->is_primary = d->is_primary;

        // set the Event interface properties
        event->d_func()->bubbles = false;
        event->d_func()->cancelable = false;
        event->d_func()->is_trusted = true;

        // set the PointerEvent interface properties
        event->d_func()->width = 1;
        event->d_func()->height = 1;
        event->d_func()->pressure = 0;
        event->d_func()->tangential_pressure = 0;
        event->d_func()->tilt_x = 0;
        event->d_func()->tilt_y = 0;
        event->d_func()->twist = 0;
        event->d_func()->altitude_angle = 0;
        event->d_func()->azimuth_angle = 0;

        event->d_func()->coalesced_events.clear();
        event->d_func()->predicted_events.clear();
    }
}


auto pointer_events::pointer_event::get_coalesced_events() const -> ext::vector_span<pointer_event*>
{
    ACCESS_PIMPL(const pointer_event);
    return d->coalesced_events;
}


auto pointer_events::pointer_event::get_predicted_events() const -> ext::vector_span<pointer_event*>
{
    ACCESS_PIMPL(const pointer_event);
    return d->predicted_events;
}


auto pointer_events::pointer_event::set_target(dom::nodes::event_target* new_target) -> dom::nodes::event_target*
{
    ACCESS_PIMPL(pointer_event);
    for (decltype(auto) event: ranges::views::concat(d->coalesced_events, d->predicted_events, ranges::views::single(this)))
        event->d_func()->target = new_target;
    return new_target;
}
