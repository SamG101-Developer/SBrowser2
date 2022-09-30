#ifndef SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP
#define SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class non_document_type_child_node;}

namespace dom::nodes {class element;}

#include "dom/mixins/non_document_type_child_node_private.hpp"


class dom::mixins::non_document_type_child_node
        : public virtual dom_object
{
public constructors:
    non_document_type_child_node();
    MAKE_PIMPL(non_document_type_child_node);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(previous_element_sibling, nodes::element*);
    DEFINE_GETTER(next_element_sibling, nodes::element*);
};


#endif //SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP
