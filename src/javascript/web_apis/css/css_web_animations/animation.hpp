#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_HPP

#include "dom/nodes/event_target.hpp"
namespace css::css_web_animations {class animation;}


#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(css/css_web_animations)
namespace css::css_web_animations {class animation_effect;}
namespace css::css_web_animations {class animation_timeline;}


#include "css/css_web_animations/animation_private.hpp"


class css::css_web_animations::animation
        : public dom::nodes::event_target
{
public constructors:
    animation();
    animation(animation_effect* effect = nullptr, animation_timeline* timeline = nullptr);

public js_methods:
    auto cancel() -> void;
    auto finish() -> void;
    auto play() -> void;
    auto pause() -> void;
    auto update_playback_rate(ext::number<double> playback_rate) -> void;
    auto reverse() -> void;
    auto persist() -> void;
    auto commit_styles();

public js_properties:
    ext::property<ext::string> id;
    ext::property<std::unique_ptr<animation_effect>> effect;
    ext::property<std::unique_ptr<animation_timeline>> timeline;

    ext::property<ext::number<double>> start_time;
    ext::property<ext::number<double>> current_time;
    ext::property<ext::number<double>> playback_rate;

    ext::property<detail::animation_play_state_t> play_state;
    ext::property<detail::animation_replace_state_t> replace_state;

    ext::property<ext::boolean> pending;
    ext::property<ext::promise<animation*>> ready;
    ext::property<ext::promise<animation*>> finished;

private cpp_members:
    MAKE_PIMPL(animation);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_HPP
