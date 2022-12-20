module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.child_node;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;

DEFINE_PUBLIC_CLASS(dom, child_node)
        : public virtual dom_object
{
public constructors:
    child_node();
    MAKE_PIMPL(child_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    template <ext::type_is<node*, ext::string> ...Args> auto before(Args&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...Args> auto after(Args&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...Args> auto replace_with(Args&&... nodes) -> node*;
    auto remove() -> nodes::node*;
};
