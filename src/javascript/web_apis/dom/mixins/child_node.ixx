module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp


export module apis.dom.mixins.child_node;
import apis._.dom_object;
import ext.type_traits;
import ext.tuple;
import js.env.module_type;

namespace dom {class node;}


DEFINE_PUBLIC_CLASS(dom, child_node)
        : public virtual dom_object
{
public constructors:
    child_node();
    MAKE_PIMPL(child_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    template <ext::type_is<node*, ext::string> ...T> auto before(T&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...T> auto after(T&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...T> auto replace_with(T&&... nodes) -> node*;
    auto remove() -> nodes::node*;
};
