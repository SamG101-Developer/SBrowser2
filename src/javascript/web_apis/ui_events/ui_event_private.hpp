#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_UI_EVENTS_UI_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_UI_EVENTS_UI_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event.hpp"

#include "ext/memory.ixx"
namespace dom::nodes {class window;}


DEFINE_PRIVATE_CLASS(ui_events, ui_event) : dom::events::event
{
    std::observer_ptr<dom::nodes::window> view;
    ext::number<long> detail;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_UI_EVENTS_UI_EVENT_PRIVATE_HPP
