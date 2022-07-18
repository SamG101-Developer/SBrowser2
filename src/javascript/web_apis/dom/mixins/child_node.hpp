#ifndef SBROWSER2_CHILD_NODE_HPP
#define SBROWSER2_CHILD_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class child_node;}

namespace dom::nodes {class node;}


class dom::mixins::child_node
        : public virtual dom_object
{
public constructors:
    child_node();

public js_methods:
    unscopable template <type_is<nodes::node*, ext::string> ...T> auto before(T&&... nodes) -> nodes::node*;
    unscopable template <type_is<nodes::node*, ext::string> ...T> auto after(T&&... nodes) -> nodes::node*;
    unscopable template <type_is<nodes::node*, ext::string> ...T> auto replace_with(T&&... nodes) -> nodes::node*;
    unscopable auto remove() -> nodes::node*;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_CHILD_NODE_HPP
