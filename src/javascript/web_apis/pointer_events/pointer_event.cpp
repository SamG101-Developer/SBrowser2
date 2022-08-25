#include "pointer_event.hpp"

#include "detail/pointer_internals.hpp"
#include "dom/nodes/event_target.hpp"

#include <range/v3/view/concat.hpp>
#include <range/v3/view/transform.hpp>


pointer_events::pointer_event::pointer_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_events::mouse_event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS(event_init, pointer_id, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, width, 1.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, height, 1.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, pressure, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(event_init, tangential_pressure, 0.0f)
        , SET_PROPERTY_FROM_OPTIONS(event_init, tilt_x, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, tilt_y, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, twist, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, altitude_angle, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, azimuth_angle, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, pointer_type, "")
        , SET_PROPERTY_FROM_OPTIONS(event_init, is_primary, false)
        , m_coalesced_events{event_init.try_emplace("coalescedEvents").first->second.to<ext::vector<pointer_event*>*>()}
        , m_predicted_events{event_init.try_emplace("predictedEvents").first->second.to<ext::vector<pointer_event*>*>()}
{
    bind_set(target);

    for_if (is_trusted(), auto* event: ranges::views::concat(*m_coalesced_events, *m_predicted_events))
    {
        // inherit these properties from his PointerEvent
        event->pointer_id = pointer_id();
        event->pointer_type = pointer_type();
        event->is_primary = is_primary();

        // set the Event interface properties
        event->bubbles = false;
        event->cancelable = false;
        event->is_trusted = true;

        // set the PointerEvent interface properties
        event->width = 1;
        event->height = 1;
        event->pressure = 0;
        event->tangential_pressure = 0;
        event->tilt_x = 0;
        event->tilt_y = 0;
        event->twist = 0;
        event->altitude_angle = 0;
        event->azimuth_angle = 0;

        event->m_coalesced_events->clear();
        event->m_predicted_events->clear();
    }
}


auto pointer_events::pointer_event::get_coalesced_events()
        const -> ext::vector<pointer_event*>*
{
    return m_coalesced_events.get();
}


auto pointer_events::pointer_event::get_predicted_events()
        const -> ext::vector<pointer_event*>*
{
    return m_predicted_events.get();
}


auto pointer_events::pointer_event::set_target(
        dom::nodes::event_target* const& val)
        -> void
{
    guard_property(target);
    (*target).reset(val);

    for (auto* event: ranges::views::concat(*m_coalesced_events, *m_predicted_events))
        event->target = target();
}
