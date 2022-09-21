#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_ANIMATION_WORKLET_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_ANIMATION_WORKLET_GLOBAL_SCOPE_HPP

#include "html/workers/worklet_global_scope.hpp"
namespace css::css_animation_worklet {class animation_worklet_global_scope;}

#include USE_INNER_TYPES(css/css_animation_worklet)


class css::css_animation_worklet::animation_worklet_global_scope
        : public html::workers::worklet_global_scope
{
public constructors:
    animation_worklet_global_scope();

public js_methods:
    auto register_animator(ext::string&& name, detail::animator_instance_constructor_t&& animator) -> void;

private cpp_members:
    MAKE_PIMPL(animation_worklet_global_scope);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_ANIMATION_WORKLET_GLOBAL_SCOPE_HPP
