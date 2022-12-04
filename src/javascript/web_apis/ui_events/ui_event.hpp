#pragma once
#ifndef SBROWSER2_UI_EVENT_HPP
#define SBROWSER2_UI_EVENT_HPP

#include "dom/events/event.hpp"
namespace ui_events {class ui_event;}
namespace ui_events {class ui_event_private;}


namespace dom::nodes {class window;}


class ui_events::ui_event
        : public dom::events::event
{
public constructors:
    ui_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(ui_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(view, dom::nodes::window*);
    DEFINE_GETTER(detail, ext::number<long>);
};


#endif //SBROWSER2_UI_EVENT_HPP
