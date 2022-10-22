#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "ui_events/mixins/modifier_event_private.hpp"


DEFINE_PRIVATE_CLASS(touch_events, touch_event) : ui_events::mixins::modifier_event_private {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_PRIVATE_HPP
