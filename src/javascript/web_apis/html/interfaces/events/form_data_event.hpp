#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_HPP


namespace html::events {class form_data_event;}
namespace html::events {class form_data_event_private;}

namespace xhr {class form_data;}


class html::events::form_data_event
        : public dom::events::event
{
public constructors:
    form_data_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(form_data_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(form_data, xhr::form_data*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_HPP
