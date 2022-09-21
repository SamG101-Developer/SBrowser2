#ifndef SBROWSER2_NON_ELEMENT_PARENT_NODE_HPP
#define SBROWSER2_NON_ELEMENT_PARENT_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class non_element_parent_node;}

namespace dom::nodes {class element;}


class dom::mixins::non_element_parent_node
        : public virtual dom_object
{
public constructors:
    non_element_parent_node() = default;

public js_methods:
    auto get_element_by_id(ext::string_view id) -> nodes::element*;

private cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_NON_ELEMENT_PARENT_NODE_HPP
