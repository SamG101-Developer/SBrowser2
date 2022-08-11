#pragma once
#ifndef SBROWSER2_WHEEL_EVENT_HPP
#define SBROWSER2_WHEEL_EVENT_HPP

#include "ui_events/mouse_event.hpp"
namespace ui_events {class wheel_event;}


class ui_events::wheel_event
        : public mouse_event
{
public constructors:
    DOM_CTORS(wheel_event);
    wheel_event() = default;
    wheel_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_static_constants:
    constexpr const static ext::number<ulong> DOM_DELTA_PIXEL = 0x00;
    constexpr const static ext::number<ulong> DOM_DELTA_LINE = 0x01;
    constexpr const static ext::number<ulong> DOM_DELTA_PAGE = 0x02;

public js_properties:
    ext::property<ext::number<double>> delta_x;
    ext::property<ext::number<double>> delta_y;
    ext::property<ext::number<double>> delta_z;
    ext::property<ext::number<ulong>> delta_mode;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_WHEEL_EVENT_HPP
