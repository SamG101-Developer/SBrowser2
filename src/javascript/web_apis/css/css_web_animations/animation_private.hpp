#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_MIXINS_ANIMATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_MIXINS_ANIMATION_PRIVATE_HPP

#include "ext/optional.ixx"
#include "ext/pimpl.ixx"

#include INCLUDE_INNER_TYPES(css/css_web_animations)

DECLARE_PRIVATE_CLASS(css::css_web_animations, animation_effect)
DECLARE_PRIVATE_CLASS(css::css_web_animations, animation_timeline)


DEFINE_PRIVATE_CLASS(css::css_web_animations, animation)
{
    std::unique_ptr<animation_effect_private> animation_effect;
    std::unique_ptr<animation_timeline_private> timeline;

    ext::optional<detail::time_value_t> start_time;
    ext::optional<detail::time_value_t> hold_time;

    ext::promise<> current_finished_promise;

    ext::number<int> playback_rate;
    ext::number<int> pending_playback_rate;

    detail::animation_replace_state_t replace_state = detail::animation_replace_state_t::ACTIVE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_MIXINS_ANIMATION_PRIVATE_HPP
