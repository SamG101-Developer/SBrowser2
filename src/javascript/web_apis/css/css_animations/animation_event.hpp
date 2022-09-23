#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_ANIMATION_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_ANIMATION_EVENT_HPP

#include "dom/events/event.hpp"
namespace css::css_animations {class animation_event;}


class css::css_animations::animation_event
        : public dom::events::event
{
public constructors:
    animation_event() = default;
    animation_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<ext::string> animation_name;
    ext::property<ext::string> pseudo_element;
    ext::property<ext::number<double>> elapsed_time;

private cpp_members:
    MAKE_V8_AVAILABLE;

public cpp_accessors:
    DEFINE_CUSTOM_GETTER(elapsed_time);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_ANIMATION_EVENT_HPP
