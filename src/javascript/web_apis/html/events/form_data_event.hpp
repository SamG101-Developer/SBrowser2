#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_HPP

#include "dom/events/event.hpp"
namespace html::events {class form_data_event;}

namespace xhr {class form_data;}


class html::events::form_data_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(form_data_event);
    form_data_event() = default;
    form_data_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<xhr::form_data*> form_data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_HPP
