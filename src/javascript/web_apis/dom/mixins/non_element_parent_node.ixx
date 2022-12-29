module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.non_element_parent_node;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom::mixins, non_element_parent_node)
        : public virtual dom_object
{
public constructors:
    non_element_parent_node();
    MAKE_PIMPL(non_element_parent_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    auto get_element_by_id(ext::string_view id) -> element*;
};
