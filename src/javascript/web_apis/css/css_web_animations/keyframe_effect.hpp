#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_KEYFRAME_EFFECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_KEYFRAME_EFFECT_HPP

#include "css/css_web_animations/animation_effect.hpp"
namespace css::css_web_animations {class keyframe_effect;}

#include USE_INNER_TYPES(css/css_web_animations)
namespace dom::nodes {class element;}


class css::css_web_animations::keyframe_effect
        : public animation_effect
{
public constructors:
    keyframe_effect();
    keyframe_effect(dom::nodes::element* element, void* key_frames, ext::variant<detail::keyframe_effect_options_t, ext::number<double>> options = {});
    keyframe_effect(keyframe_effect* source);

public js_methods:
    template <typename T> auto get_keyframes() -> ext::vector<T*>;
    template <typename T> auto set_keyframes(ext::vector_view<T> keyframes) -> void;

public js_properties:
    ext::property<std::unique_ptr<dom::nodes::element>> target;
    ext::property<ext::string> pseudo_element;
    ext::property<detail::composite_operation_t> composite;

private cpp_members:
    MAKE_PIMPL(keyframe_effect);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_KEYFRAME_EFFECT_HPP
