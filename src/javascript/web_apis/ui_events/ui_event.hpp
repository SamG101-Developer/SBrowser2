#pragma once
#ifndef SBROWSER2_UI_EVENT_HPP
#define SBROWSER2_UI_EVENT_HPP

#include "dom/events/event.hpp"
namespace ui_events {class ui_event;}

#include "ext/number.hpp"
namespace dom::nodes {class window;}


class ui_events::ui_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(ui_event);
    ui_event() = default;
    ui_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<dom::nodes::window*> view;
    ext::property<ext::number<long>> detail;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_UI_EVENT_HPP
