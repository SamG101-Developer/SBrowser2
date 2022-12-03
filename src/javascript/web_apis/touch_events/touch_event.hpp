#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_HPP

#include "ui_events/mixins/modifier_event.hpp"
namespace touch_events {class touch_event;}
namespace touch_events {class touch_event_private;}


namespace touch_events {class touch;}


class touch_events::touch_event
        : public ui_events::mixins::modifier_event
{
public constructors:
    touch_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(touch_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(touches, ranges::any_helpful_view<touch*>);
    DEFINE_GETTER(target_touches, ranges::any_helpful_view<touch*>);
    DEFINE_GETTER(changed_touches, ranges::any_helpful_view<touch*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_HPP
