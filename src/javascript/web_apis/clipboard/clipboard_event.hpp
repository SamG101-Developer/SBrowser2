#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_EVENT_HPP

#include "dom/events/event.hpp"
namespace clipboard {class clipboard_event;}

namespace html::dnd {class data_transfer;}

class clipboard::clipboard_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(clipboard_event);
    clipboard_event() = default;
    clipboard_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<html::dnd::data_transfer*> clipboard_data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_EVENT_HPP
