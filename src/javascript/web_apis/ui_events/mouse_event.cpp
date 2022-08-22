#include "mouse_event.hpp"

#include "ui_events/mixins/modifier_event.hpp"


ui_events::mouse_event::mouse_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : mixins::modifier_event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS(event_init, screen_x, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, screen_y, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, client_x, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, client_y, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, buttons, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, button, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, movement_x, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, movement_y, 0)
{}


auto ui_events::mouse_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<mouse_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<mixins::modifier_event>()
            .var("screenX", &mouse_event::screen_x, true)
            .var("screenY", &mouse_event::screen_y, true)
            .var("clientX", &mouse_event::client_x, true)
            .var("clientY", &mouse_event::client_y, true)
            .var("button", &mouse_event::button, true)
            .var("buttons", &mouse_event::buttons, true)
            .var("movementX", &mouse_event::movement_x, true)
            .var("movementY", &mouse_event::movement_y, true)
            .auto_wrap_objects();
}
