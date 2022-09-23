#pragma once
#ifndef SBROWSER2_KEYBOARD_EVENT_HPP
#define SBROWSER2_KEYBOARD_EVENT_HPP

#include "ui_events/mixins/modifier_event.hpp"
namespace ui_events {class keyboard_event;}


class ui_events::keyboard_event
        : public mixins::modifier_event
{
public constructors:
    DOM_CTORS(keyboard_event);
    keyboard_event() = default;
    keyboard_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_static_constants:
    constexpr const static ext::number<ulong> DOM_KEY_LOCATION_STANDARD = 0x00;
    constexpr const static ext::number<ulong> DOM_KEY_LOCATION_LEFT = 0x01;
    constexpr const static ext::number<ulong> DOM_KEY_LOCATION_RIGHT = 0x02;
    constexpr const static ext::number<ulong> DOM_KEY_LOCATION_NUMPAD = 0x03;

private js_properties:
    ext::property<ext::string> key;
    ext::property<ext::number<ushort>> code;
    ext::property<ext::number<ulong>> location;

    ext::property<ext::boolean> repeat;
    ext::property<ext::boolean> is_composing;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_KEYBOARD_EVENT_HPP
