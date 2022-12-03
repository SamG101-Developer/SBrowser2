#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/events/event_private.hpp"

namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::events, submit_event) : dom::events::event_private
{
    std::unique_ptr<html::elements::html_form_element> submitter;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_SUBMIT_EVENT_PRIVATE_HPP
