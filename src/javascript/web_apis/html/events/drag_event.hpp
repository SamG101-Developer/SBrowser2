#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_HPP

#include "dom/events/event.hpp"
namespace html::events {class drag_event;}
namespace html::events {class drag_event_private;}

namespace html::dnd {class data_transfer;}


class html::events::drag_event
        : public dom::events::event
{
public constructors:
    drag_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    DOM_CTORS(drag_event);
    MAKE_PIMPL(drag_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(data_transfer, dnd::data_transfer*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_HPP
