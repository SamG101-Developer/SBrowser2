#include "pointer_event.hpp"

#include "detail/pointer_internals.hpp"
#include "dom/nodes/event_target.hpp"

#include <range/v3/view/concat.hpp>
#include <range/v3/view/transform.hpp>


pointer_events::pointer_event::pointer_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_events::mouse_event{std::move(event_type), std::move(event_init)}
        , pointer_id{event_init.try_emplace("pointerId", 0).first->second.to<ext::number<long>>()}
        , width{event_init.try_emplace("width", 1).first->second.to<ext::number<double>>()}
        , height{event_init.try_emplace("height", 1).first->second.to<ext::number<double>>()}
        , pressure{event_init.try_emplace("pressure", 0).first->second.to<ext::number<float>>()}
        , tangential_pressure{event_init.try_emplace("tangentialPressure", 0).first->second.to<ext::number<float>>()}
        , tilt_x{event_init.try_emplace("tiltX").first->second.to<ext::number<long>>()}
        , tilt_y{event_init.try_emplace("tiltY").first->second.to<ext::number<long>>()}
        , twist{event_init.try_emplace("twist", 0).first->second.to<ext::number<long>>()}
        , altitude_angle{event_init.try_emplace("altitudeAngle").first->second.to<ext::number<double>>()}
        , azimuth_angle{event_init.try_emplace("azimuthAngle").first->second.to<ext::number<double>>()}
        , pointer_type{event_init.try_emplace("pointerType", "").first->second.to<ext::number<ext::string>>()}
        , is_primary{event_init.try_emplace("isPrimary", false).first->second.to<ext::number<ext::boolean>>()}
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
        dom::nodes::event_target* val)
        -> void
{
    property_guard(target);
    (*target).reset(val);

    for (auto* event: ranges::views::concat(*m_coalesced_events, *m_predicted_events))
        event->target = target();
}
