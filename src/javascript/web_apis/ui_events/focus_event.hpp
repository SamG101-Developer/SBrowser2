#pragma once
#ifndef SBROWSER2_FOCUS_EVENT_HPP
#define SBROWSER2_FOCUS_EVENT_HPP

#include "ui_events/ui_event.hpp"
namespace ui_events {class focus_event;}

class ui_events::focus_event
        : public ui_event
{
public constructors:
    DOM_CTORS(focus_event);
    focus_event() = default;
    focus_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public cpp_methods:
    ext::any to_v8(v8::Isolate *isolate) const && override;
};


#endif //SBROWSER2_FOCUS_EVENT_HPP
