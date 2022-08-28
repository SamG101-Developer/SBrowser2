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
    DOM_CTORS(animation_worklet_global_scope);
    animation_worklet_global_scope() = default;

public js_methods:
    auto register_animator(ext::string&& name, detail::animator_instance_constructor_t&& animator) -> void;

private cpp_properties:
    ext::map<ext::string, detail::animator_definition_t*> m_animator_definitions;
    ext::vector<detail::animator_instance_t*> m_animator_instance_set;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_ANIMATION_WORKLET_GLOBAL_SCOPE_HPP
