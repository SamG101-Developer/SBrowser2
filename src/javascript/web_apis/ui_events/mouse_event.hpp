#pragma once
#ifndef SBROWSER2_MOUSE_EVENT_HPP
#define SBROWSER2_MOUSE_EVENT_HPP

#include "ui_events/mixins/modifier_event.hpp"
namespace ui_events {class mouse_event;}

class ui_events::mouse_event
        : public mixins::modifier_event
{
public constructors:
    DOM_CTORS(mouse_event);
    mouse_event() = default;
    mouse_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<ext::number<long>> screen_x;
    ext::property<ext::number<long>> screen_y;
    ext::property<ext::number<long>> client_x;
    ext::property<ext::number<long>> client_y;

    ext::property<ext::number<short>> button;
    ext::property<ext::number<ushort>> buttons;

    /* POINTER_LOCK */
    ext::property<ext::number<double>> movement_x;
    ext::property<ext::number<double>> movement_y;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_MOUSE_EVENT_HPP
