#include "gamepad_button.hpp"
#include "gamepad_button_private.hpp"


gamepad::gamepad_button::gamepad_button()
{
    INIT_PIMPL(gamepad_button);
}


auto gamepad::gamepad_button::get_pressed() const -> ext::boolean
{
    ACCESS_PIMPL(const gamepad_button);
    return d->pressed;
}


auto gamepad::gamepad_button::get_touched() const -> ext::boolean
{
    ACCESS_PIMPL(const gamepad_button);
    return d->touched;
}


auto gamepad::gamepad_button::get_value() const -> ext::number<double>
{
    ACCESS_PIMPL(const gamepad_button);
    return d->value;
}


auto gamepad::gamepad_button::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<gamepad_button>{isolate}
        .inherit<dom_object>()
        .property("pressed", &gamepad_button::get_pressed)
        .property("touched", &gamepad_button::get_touched)
        .property("value", &gamepad_button::get_value)
        .auto_wrap_objects();

    return std::move(conversion);
}
