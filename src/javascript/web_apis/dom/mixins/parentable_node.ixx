module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.parentable_node;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom::mixins, parentable_node)
        : public virtual dom_object
{
public constructors:
    parentable_node();
    MAKE_PIMPL(parentable_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    template <ext::type_is<node*, ext::string> ...T> auto prepend(T&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...T> auto append(T&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...T> auto replace_children(T&&... nodes) -> node*;

    auto query_selector(ext::string_view selectors) -> element*;
    auto query_selector_all(ext::string_view selectors) -> ext::vector<element*>;

private js_properties:
    DEFINE_GETTER(children, ranges::any_helpful_view<element*>);
    DEFINE_GETTER(first_element_child, element*);
    DEFINE_GETTER(last_element_child, element*);
    DEFINE_GETTER(child_element_count, ext::number<size_t>);
};
