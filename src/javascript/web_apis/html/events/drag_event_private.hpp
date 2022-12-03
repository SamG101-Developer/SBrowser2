#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/events/event_private.hpp"

#include "html/dnd/data_transfer.hpp"


DEFINE_PRIVATE_CLASS(html::events, drag_event) : dom::events::event_private
{
    std::unique_ptr<dnd::data_transfer> data_transfer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_DRAG_EVENT_PRIVATE_HPP
