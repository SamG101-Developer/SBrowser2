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

public js_properties:
    ext::property<ext::string> animation_name;
    ext::property<ext::string> pseudo_element;
    ext::property<ext::number<double>> elapsed_time;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_ANIMATION_EVENT_HPP
