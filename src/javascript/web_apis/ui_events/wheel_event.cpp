#include "wheel_event.hpp"


ui_events::wheel_event::wheel_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : mouse_event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS(event_init, delta_x, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, delta_y, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, delta_z, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, delta_mode, 0)
{}


auto ui_events::wheel_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<wheel_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<mouse_event>()
            .static_("DOM_DELTA_PIXEL", wheel_event::DOM_DELTA_PIXEL, true)
            .static_("DOM_DELTA_LINE", wheel_event::DOM_DELTA_LINE, true)
            .static_("DOM_DELTA_PAGE", wheel_event::DOM_DELTA_PAGE, true)
            .var("deltaX", &wheel_event::delta_x, true)
            .var("deltaY", &wheel_event::delta_y, true)
            .var("deltaZ", &wheel_event::delta_z, true)
            .var("deltaMode", &wheel_event::delta_mode, true)
            .auto_wrap_objects();
}
