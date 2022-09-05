#include "gamepad_button.hpp"
#include "dom_object.hpp"


auto gamepad::gamepad_button::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<gamepad_button>{isolate}
        .inherit<dom_object>()
        .var("pressed", &gamepad_button::pressed, true)
        .var("touched", &gamepad_button::touched, true)
        .var("value", &gamepad_button::value, true)
        .slot("pressed", &gamepad_button::s_pressed)
        .slot("touched", &gamepad_button::s_touched)
        .slot("value", &gamepad_button::s_value)
        .auto_wrap_objects();
}
