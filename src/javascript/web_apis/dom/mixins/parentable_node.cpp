#include "parentable_node.ixx"
#include "parentable_node_private.ixx"




#include "dom/_typedefs.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/nodes/window.hpp"

#include <range/v3/view/remove.hpp>


template <ext::type_is<dom::nodes::node*, ext::string> ...T>
auto dom::mixins::parentable_node::prepend(T&&... nodes) -> nodes::node*
{
    // Parse the 'nodes' parameter, and pre-insert the derived 'node' into this's child nodes, before the first node in
    // the child nodes list.
    CE_REACTIONS_METHOD_DEF
        decltype(auto) base = ext::cross_cast<nodes::node*>(this);
        decltype(auto) node = detail::convert_nodes_into_node(base->d_func()->node_document, std::forward<T>(nodes)...);
        detail::pre_insert(node, base, base->d_func()->child_nodes.front());
        return node;
    CE_REACTIONS_METHOD_EXE
}


template <ext::type_is<dom::nodes::node*, ext::string> ...T>
auto dom::mixins::parentable_node::append(T&&... nodes) -> nodes::node*
{
    // Parse the 'nodes' parameter, and append the derived 'node' into this's child nodes, after the first node in the
    // child nodes list.
    CE_REACTIONS_METHOD_DEF
        decltype(auto) base = ext::cross_cast<nodes::node*>(this);
        decltype(auto) node = detail::convert_nodes_into_node(base->d_func()->node_document, std::forward<T>(nodes)...);
        detail::append(node, base, base->d_func()->child_nodes.front());
        return node;
    CE_REACTIONS_METHOD_EXE
}


template <ext::type_is<dom::nodes::node*, ext::string> ...T>
auto dom::mixins::parentable_node::replace_children(T&&... nodes) -> nodes::node*
{
    // Parse the 'nodes' parameter, and replace the derived 'node' from this's child nodes, after ensuring pre insertion
    // validity of the node, at the end of the child nodes list.
    CE_REACTIONS_METHOD_DEF
        decltype(auto) base = ext::cross_cast<nodes::node*>(this);
        decltype(auto) node = detail::convert_nodes_into_node(base->d_func()->node_document, std::forward<T>(nodes)...);
        detail::ensure_pre_insertion_validity(node, base, nullptr);
        detail::replace_all(node, base);
        return node;
    CE_REACTIONS_METHOD_EXE
}


auto dom::mixins::parentable_node::get_children() const -> ranges::any_helpful_view<nodes::element*>
{
    // The 'children' getter returns the equivalent 'children' attribute value that is stored in the private class.
    ACCESS_PIMPL(const parentable_node);
    return d->children;
}


auto dom::mixins::parentable_node::get_first_element_child() const -> nodes::element*
{
    // The 'first_element_child' getter returns the first element from the 'chidren' attribute value that is stored in
    // the private class.
    ACCESS_PIMPL(const parentable_node);
    return d->children.empty() ? nullptr : d->children.front();
}


auto dom::mixins::parentable_node::get_last_element_child() const -> nodes::element*
{
    // The 'last_element_child' getter returns the last element from the 'children' attribute value that is stored in
    // the private class.
    ACCESS_PIMPL(const parentable_node);
    return d->children.empty() ? nullptr : d->children.back();
}


auto dom::mixins::parentable_node::get_child_element_count() const -> ext::number<size_t>
{
    // The 'child_element_count' getter returns the number of elements in 'children' attribute value that is stored in
    // the private class.
    ACCESS_PIMPL(const parentable_node);
    return d->children.size();
}


auto dom::mixins::parentable_node::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("prepend", &parentable_node::prepend, UNSCOPABLE)
        .function("append", &parentable_node::append, UNSCOPABLE)
        .function("replaceChildren", &parentable_node::replace_children, UNSCOPABLE)
        .function("querySelector", &parentable_node::query_selector)
        .function("querySelectorAll", &parentable_node::query_selector_all)
        .property("children", &parentable_node::get_children)
        .property("firstElementChild", &parentable_node::get_first_element_child)
        .property("lastElementChild", &parentable_node::get_last_element_child)
        .property("childElementCount", &parentable_node::get_child_element_count)
        .auto_wrap_objects();
    
    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
