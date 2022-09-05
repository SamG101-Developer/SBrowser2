#include "gamepad_event.hpp"

#include "gamepad/gamepad.hpp"


gamepad::gamepad_event::gamepad_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS(event_init, gamepad, nullptr)
{}


auto gamepad::gamepad_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<gamepad_event>{isolate}
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .inherit<dom::events::event>()
        .var("gamepad", &gamepad_event::gamepad, true)
        .auto_wrap_objects();
}
