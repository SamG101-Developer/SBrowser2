#pragma once
#ifndef SBROWSER2_INPUT_EVENT_HPP
#define SBROWSER2_INPUT_EVENT_HPP

#include "ui_events/ui_event.hpp"
namespace ui_events {class input_event;}


class ui_events::input_event
        : public ui_event
{
public constructors:
    DOM_CTORS(input_event);
    input_event() = default;
    input_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    /* UI_EVENTS */
    ext::property<ext::string> data;
    ext::property<ext::string> input_type;
    ext::property<ext::boolean> is_composing;

    /* INPUT_EVENTS */
    // TODO

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_INPUT_EVENT_HPP
