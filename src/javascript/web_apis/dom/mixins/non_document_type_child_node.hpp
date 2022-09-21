#ifndef SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP
#define SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class non_document_type_child_node;}

namespace dom::nodes {class element;}


class dom::mixins::non_document_type_child_node
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(non_document_type_child_node);
    non_document_type_child_node();

public js_properties:
    ext::property<nodes::element*> previous_element_sibling;
    ext::property<nodes::element*> next_element_sibling;

private cpp_members:
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(previous_element_sibling);
    DEFINE_CUSTOM_GETTER(next_element_sibling);
};


#endif //SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP
