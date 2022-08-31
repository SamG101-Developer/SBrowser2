#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_HPP

#include "dom/events/event.hpp"
namespace html::events {class submit_event;}

namespace html::elements {class html_form_element;}


class html::events::submit_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(submit_event);
    submit_event() = default;
    submit_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<elements::html_form_element*> submitter;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_HPP
