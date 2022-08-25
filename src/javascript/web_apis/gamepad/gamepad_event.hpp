#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP

#include "dom/events/event.hpp"
namespace gamepad {class gamepad_event;}


class gamepad_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(gamepad_event);
    gamepad_event() = default;
    gamepad_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::boolean> pressed;
    ext::property<ext::boolean> touched;
    ext::property<ext::number<double>> value;

private js_slots:
    ext::slot<ext::boolean> s_pressed;
    ext::slot<ext::boolean> s_touched;
    ext::slot<ext::number<double>> s_value;

private cpp_accessors:
    DEFINE_GETTER(pressed);
    DEFINE_GETTER(touched);
    DEFINE_GETTER(value);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP
