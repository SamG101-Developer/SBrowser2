#include "gamepad_event.ixx"
#include "gamepad_event_private.ixx"

#include "gamepad/gamepad.hpp"


gamepad::gamepad_event::gamepad_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(gamepad_event);
    ACCESS_PIMPL(gamepad_event);

    d->gamepad = event_init[u"gamepad"].to<gamepad*>();
}


auto gamepad::gamepad_event::get_gamepad() const -> gamepad*
{
    ACCESS_PIMPL(const gamepad_event);
    return d->gamepad.get();
}


auto gamepad::gamepad_event::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<gamepad_event>{isolate}
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .inherit<dom::events::event>()
        .property("gamepad", &gamepad_event::get_gamepad)
        .auto_wrap_objects();

    return std::move(conversion);
}
