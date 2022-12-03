#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "ui_events/mixins/modifier_event_private.hpp"

namespace touch_events {class touch;}


DEFINE_PRIVATE_CLASS(touch_events, touch_event) : ui_events::mixins::modifier_event_private
{
    ext::vector<std::unique_ptr<touch>> touches;
    ext::vector<std::unique_ptr<touch>> target_touches;
    ext::vector<std::unique_ptr<touch>> changed_touches;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_PRIVATE_HPP
