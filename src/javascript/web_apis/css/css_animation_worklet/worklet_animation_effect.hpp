#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_WORKLET_ANIMATION_EFFECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_WORKLET_ANIMATION_EFFECT_HPP

#include "dom_object.hpp"
namespace css::css_animation_worklet {class worklet_animation_effect;}

#include USE_INNER_TYPES(css/css_animation_worklet)


class css::css_animation_worklet::worklet_animation_effect
        : public dom_object
{
public constructors:
    DOM_CTORS(worklet_animation_effect)
    worklet_animation_effect() = default;

public js_methods:
    auto get_timing() -> detail::effect_timing_t&;
    auto get_computed_timing() -> computed_effect_timing_t&;

public js_properties:
    ext::property<double> local_time;

private cpp_properties:
    std::unique_ptr<detail::animator_effect_t> m_animator_effect;

private cpp_accessors:
    DEFINE_GETTER(local_time);
    DEFINE_SETTER(local_time);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_WORKLET_ANIMATION_EFFECT_HPP
