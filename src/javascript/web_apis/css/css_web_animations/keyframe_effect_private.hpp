#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_KEYFRAME_EFFECT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_KEYFRAME_EFFECT_PRIVATE_HPP

#include "ext/optional.ixx"
#include "ext/pimpl.ixx"
#include "css/css_web_animations/animation_effect_private.hpp"

#include INCLUDE_INNER_TYPES(css/css_web_animations)


DEFINE_PRIVATE_CLASS(css::css_web_animations, keyframe_effect) : animation_effect_private
{
    ext::optional<ext::number<double>> offset;
    ext::vector<detail::keyframe_t> keyframes;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_KEYFRAME_EFFECT_PRIVATE_HPP
