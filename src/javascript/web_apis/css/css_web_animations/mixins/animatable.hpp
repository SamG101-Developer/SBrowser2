#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_MIXINS_ANIMATABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_MIXINS_ANIMATABLE_HPP

#include "dom_object.hpp"
namespace css::css_web_animations::mixins {class animatable;}


#include INCLUDE_INNER_TYPES(css/css_web_animations)
namespace css::css_web_animations {class animation;}


class css::css_web_animations::mixins::animatable
        : public virtual dom_object
{
public js_methods:
    auto animate(void* keyframes, ext::variant<detail::keyframe_animation_options_t, ext::number<double>> = {}) -> animation;
    auto get_animations(detail::get_animations_options_t&& options = {}) -> ext::vector<animation*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_MIXINS_ANIMATABLE_HPP
