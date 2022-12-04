#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_EFFECT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_EFFECT_PRIVATE_HPP

#include "ext/map.ixx"


#include "ext/pimpl.ixx"

#include INCLUDE_INNER_TYPES(css)
#include INCLUDE_INNER_TYPES(css/css_web_animations)


DEFINE_PRIVATE_CLASS(css::css_web_animations, animation_effect)
{
    ext::pair<ext::number<int>, ext::number<int>> active_internal;
    ext::number<int> start_delay;
    ext::number<int> end_delay;

    ext::number<int> iteration_interval;
    ext::number<int> iteration_duration;
    ext::number<int> iteration_count;
    ext::number<int> iteration_start;

    ext::map<detail::abstract_property_t*, ext::number<int>> target_properties;

    detail::keyframe_operation_t keyframe_specific_composite_operation;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_EFFECT_PRIVATE_HPP
