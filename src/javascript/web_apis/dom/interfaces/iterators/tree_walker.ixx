module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.tree_walker;
import apis.dom.abstract_iterator;

import apis.dom.types;
import ext.core;
import js.env.module_type;



DEFINE_PUBLIC_CLASS(dom, tree_walker)
        : public dom::abstract_iterator
{
public constructors:
    tree_walker();
    MAKE_PIMPL(tree_walker);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto parent_node() -> node*;
    auto first_child() -> node*;
    auto last_child() -> node*;
    auto next_sibling() -> node*;
    auto prev_sibling() -> node*;
    auto next_node() -> node*;
    auto prev_node() -> node*;

private js_properties:
    DEFINE_GETTER(current_node, node*);
    DEFINE_SETTER(current_node, node*);
};
