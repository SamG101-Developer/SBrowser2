#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_HPP


namespace html::events {class submit_event;}
namespace html::events {class submit_event_private;}

namespace html::elements {class html_form_element;}


class html::events::submit_event
        : public dom::events::event
{
public constructors:
    submit_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(submit_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(submitter, html::elements::html_form_element*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_HPP
