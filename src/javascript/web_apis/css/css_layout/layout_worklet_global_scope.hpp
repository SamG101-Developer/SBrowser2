#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT_LAYOUT_WORKLET_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT_LAYOUT_WORKLET_GLOBAL_SCOPE_HPP

#include "html/workers/worklet_global_scope.hpp"
namespace css::css_layout {class layout_worklet_global_scope;}

#include USE_INNER_TYPES(.)


class css::css_layout::layout_worklet_global_scope
        : public html::workers::worklet_global_scope
{
public constructors:
    layout_worklet_global_scope() = default;

public js_methods:
    auto register_layout(ext::string&& name, ext::function<void()>&& layout_constructor);

private cpp_properties:
    ext::map<ext::string, detail::layout_definition_t*> m_animator_definitions;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT_LAYOUT_WORKLET_GLOBAL_SCOPE_HPP
