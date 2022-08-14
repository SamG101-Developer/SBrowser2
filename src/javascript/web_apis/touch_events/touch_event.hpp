#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_HPP

#include "ui_events/mixins/modifier_event.hpp"
namespace touch_events {class touch_event;}

#include "touch_events/touch.hpp"

class touch_events::touch_event
        : public ui_events::mixins::modifier_event
{
public constructors:
    touch_event() = default;
    touch_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<std::unique_ptr<ext::vector<touch*>>> touches;
    ext::property<std::unique_ptr<ext::vector<touch*>>> target_touches;
    ext::property<std::unique_ptr<ext::vector<touch*>>> changed_touches;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_EVENT_HPP
