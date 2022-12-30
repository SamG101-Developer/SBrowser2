module;
#include "ext/macros.hpp"


export module apis.dom.node_iterator;
import apis.dom.abstract_iterator;
import ext.core;
import js.env.module_type;

namespace dom {class node;}


DEFINE_PUBLIC_CLASS(dom, node_iterator) final
        : public dom::abstract_iterator
{
public constructors:
    node_iterator();
    MAKE_PIMPL(node_iterator);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto next_node() -> node*;
    auto prev_node() -> node*;

private js_properties:
    DEFINE_GETTER(reference_node, node*);
    DEFINE_GETTER(pointer_before_reference_node, ext::boolean);
};
