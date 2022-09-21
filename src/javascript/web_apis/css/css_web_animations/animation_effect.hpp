#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_EFFECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_EFFECT_HPP

#include "dom_object.hpp"
namespace css::css_web_animations {class animation_effect;}

#include USE_INNER_TYPES(css/css_web_animations)


class css::css_web_animations::animation_effect
        : public virtual dom_object
{
public constructors:
    animation_effect() = default;

public js_methods:
    auto get_timing() -> detail::effect_timing_t;
    auto get_computed_timing() -> detail::computed_effect_timing_t;
    auto update_timing(detail::optional_effect_timing_t&& timing = {}) -> void;

private cpp_members:
    MAKE_PIMPL(animation_effect);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_EFFECT_HPP
