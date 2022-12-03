#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/events/event_private.hpp"

namespace xhr {class form_data;}


DEFINE_PRIVATE_CLASS(html::events, form_data_event) : dom::events::event_private
{
    std::unique_ptr<xhr::form_data> form_data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_FORM_DATA_EVENT_PRIVATE_HPP
