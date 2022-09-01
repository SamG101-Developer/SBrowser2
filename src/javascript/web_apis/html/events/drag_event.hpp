#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_HPP

#include "dom/events/event.hpp"
namespace html::events {class drag_event;}

namespace html::dnd {class data_transfer;}


class html::events::drag_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(drag_event);
    drag_event() = default;
    drag_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<std::unique_ptr<dnd::data_transfer>> data_transfer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_HPP
