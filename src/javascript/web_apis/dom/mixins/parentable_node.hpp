#ifndef SBROWSER2_PARENTABLE_NODE_HPP
#define SBROWSER2_PARENTABLE_NODE_HPP


namespace dom::mixins {class parentable_node;}
namespace dom::mixins {class parentable_node_private;}


#include "ext/type_traits.ixx"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}


class dom::mixins::parentable_node
        : public virtual dom_object
{
public constructors:
    parentable_node();
    MAKE_PIMPL(parentable_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    template <ext::type_is<nodes::node*, ext::string> ...T> auto prepend(T&&... nodes) -> nodes::node*;
    template <ext::type_is<nodes::node*, ext::string> ...T> auto append(T&&... nodes) -> nodes::node*;
    template <ext::type_is<nodes::node*, ext::string> ...T> auto replace_children(T&&... nodes) -> nodes::node*;

    auto query_selector(ext::string_view selectors) -> nodes::element*; // TODO: return type
    auto query_selector_all(ext::string_view selectors) -> ext::vector<nodes::element*>; // TODO: return type

private js_properties:
    DEFINE_GETTER(children, ranges::any_helpful_view<nodes::element*>);
    DEFINE_GETTER(first_element_child, nodes::element*);
    DEFINE_GETTER(last_element_child, nodes::element*);
    DEFINE_GETTER(child_element_count, ext::number<size_t>);
};


#endif //SBROWSER2_PARENTABLE_NODE_HPP
