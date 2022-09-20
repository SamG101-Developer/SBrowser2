#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_TIMELINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_TIMELINE_HPP

#include "dom_object.hpp"
namespace css::css_web_animations {class animation_timeline;}

#include USE_INNER_TYPES(css/css_web_animations)


class css::css_web_animations::animation_timeline
        : public virtual dom_object
{
public constructors:
    animation_timeline() = default;

public js_properties:
    ext::property<ext::number<double>> current_time;

private cpp_properties:
    std::unique_ptr<detail::timeline_t> m_timeline;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_TIMELINE_HPP
