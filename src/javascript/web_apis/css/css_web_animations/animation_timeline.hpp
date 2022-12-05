#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_TIMELINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_TIMELINE_HPP


namespace css::css_web_animations {class animation_timeline;}

#include "css/css_web_animations/animation_timeline_private.hpp"
#include INCLUDE_INNER_TYPES(css/css_web_animations)


class css::css_web_animations::animation_timeline
        : public virtual dom_object
{
public constructors:
    animation_timeline() = default;

private js_properties:
    ext::property<ext::number<double>> current_time;

private cpp_members:
    MAKE_PIMPL(animation_timeline);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_TIMELINE_HPP
