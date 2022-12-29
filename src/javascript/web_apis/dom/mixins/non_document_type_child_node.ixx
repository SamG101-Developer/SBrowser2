module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.non_document_type_child_node;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom::mixins, non_document_type_child_node)
        : public virtual dom_object
{
public constructors:
    non_document_type_child_node();
    MAKE_PIMPL(non_document_type_child_node);
    MAKE_V8_AVAILABLE(MIXIN);

private js_properties:
    DEFINE_GETTER(previous_element_sibling, element*);
    DEFINE_GETTER(next_element_sibling, element*);
};
