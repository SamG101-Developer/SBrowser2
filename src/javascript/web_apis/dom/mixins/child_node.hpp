#ifndef SBROWSER2_CHILD_NODE_HPP
#define SBROWSER2_CHILD_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class child_node;}
namespace dom::mixins {class child_node_private;}

#include "ext/concepts.hpp"
namespace dom::nodes {class node;}


class dom::mixins::child_node
        : public virtual dom_object
{
public constructors:
    child_node();
    MAKE_PIMPL(child_node);
    MAKE_V8_AVAILABLE;

public js_methods:
    template <ext::type_is<nodes::node*, ext::string> ...T> auto before(T&&... nodes) -> nodes::node*;
    template <ext::type_is<nodes::node*, ext::string> ...T> auto after(T&&... nodes) -> nodes::node*;
    template <ext::type_is<nodes::node*, ext::string> ...T> auto replace_with(T&&... nodes) -> nodes::node*;
    auto remove() -> nodes::node*;
};


#endif //SBROWSER2_CHILD_NODE_HPP
