#include "non_document_type_child_node.hpp"
#include "non_document_type_child_node_private.hpp"

#include "ext/casting.ixx"


#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"

#include <range/v3/algorithm/find.hpp>
#include <range/v3/view/slice.hpp>
#include <range/v3/view/subrange.hpp>


auto dom::mixins::non_document_type_child_node::get_previous_element_sibling() const -> nodes::element*
{
    // Get all the child nodes from this object's parent node#. All the child nodes are stored as Node pointers, so cast
    // them all to Element pointers, and get all the nodes before this object (cast as a Node object). Return the back
    // of this list; this is the previous sibling.
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) siblings = base->d_func()->parent_node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<nodes::node>::get);
    decltype(auto) previous_siblings = ranges::subrange(siblings.begin(), ranges::find(siblings, base));
    return ranges::back(previous_siblings | ranges::views::cast<nodes::element*>);
}


auto dom::mixins::non_document_type_child_node::get_next_element_sibling() const -> nodes::element*
{
    // Get all the child nodes from this object's parent node#. All the child nodes are stored as Node pointers, so cast
    // them all to Element pointers, and get all the nodes after this object (cast as a Node object). Return the front
    // of this list; this is the next sibling.
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) siblings = base->d_func()->parent_node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<nodes::node>::get);
    decltype(auto) next_siblings = ranges::subrange(ranges::find(siblings, base), siblings.end());
    return ranges::front(next_siblings | ranges::views::cast<nodes::element*>);
}


auto dom::mixins::non_document_type_child_node::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("previousElementSibling", &non_document_type_child_node::get_previous_element_sibling)
        .property("nextElementSibling", &non_document_type_child_node::get_next_element_sibling)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
