#pragma once
#ifndef SBROWSER2_COMPOSITION_EVENT_HPP
#define SBROWSER2_COMPOSITION_EVENT_HPP

#include "ui_events/ui_event.hpp"
namespace ui_events {class composition_event;}


class ui_events::composition_event
        : public ui_event
{
public constructors:
    DOM_CTORS(composition_event);
    composition_event() = default;
    composition_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<ext::string> data;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_COMPOSITION_EVENT_HPP
