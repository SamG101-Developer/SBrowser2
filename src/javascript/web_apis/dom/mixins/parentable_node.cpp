#include "parentable_node.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/nodes/window.hpp"

#include <range/v3/view/remove.hpp>


dom::mixins::parentable_node::parentable_node()
{
    bind_get(children);
    bind_get(first_element_child);
    bind_get(last_element_child);
    bind_get(child_element_count);
}


template <type_is<dom::nodes::node*, ext::string> ...T>
auto dom::mixins::parentable_node::prepend(
        T&&... nodes)
        -> nodes::node*
{
    // parse the 'nodes' parameter, and pre insert the derived 'node' into this's child nodes, before the first node in
    // the child nodes list
    CE_REACTIONS_METHOD_DEF
        decltype(auto) base = ext::cross_cast<nodes::node*>(this);
        decltype(auto) node = detail::convert_nodes_into_node(base->owner_document(), std::forward<T>(nodes)...);
        detail::pre_insert(node, base, base->child_nodes()->front());
        return node;
    CE_REACTIONS_METHOD_EXE
}


template <type_is<dom::nodes::node*, ext::string> ...T>
auto dom::mixins::parentable_node::append(
        T&&... nodes)
        -> nodes::node*
{
    // parse the 'nodes' parameter, and append the derived 'node' into this's child nodes, after the first node in the
    // child nodes list
    CE_REACTIONS_METHOD_DEF
        decltype(auto) base = ext::cross_cast<nodes::node*>(this);
        decltype(auto) node = detail::convert_nodes_into_node(base->owner_document(), std::forward<T>(nodes)...);
        detail::append(node, base, base->child_nodes()->front());
        return node;
    CE_REACTIONS_METHOD_EXE
}


template <type_is<dom::nodes::node*, ext::string> ...T>
auto dom::mixins::parentable_node::replace_children(
        T&&... nodes)
        -> nodes::node*
{
    // parse the 'nodes' parameter, and replace the derived 'node' from this's child nodes, after ensuring pre insertion
    // validity of the node, at the end of the child nodes list
    CE_REACTIONS_METHOD_DEF
        decltype(auto) base = ext::cross_cast<nodes::node*>(this);
        decltype(auto) node = detail::convert_nodes_into_node(base->owner_document(), std::forward<T>(nodes)...);
        detail::ensure_pre_insertion_validity(node, base, nullptr);
        detail::replace_all(node, base);
        return node;
    CE_REACTIONS_METHOD_EXE
}


auto dom::mixins::parentable_node::get_children()
        const -> decltype(this->children)::value_t
{
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) child_nodes = *base->child_nodes();
    return child_nodes | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::element*>();
}


auto dom::mixins::parentable_node::get_first_element_child() const -> decltype(this->first_element_child)::value_t
{return children().front();}


auto dom::mixins::parentable_node::get_last_element_child() const -> decltype(this->last_element_child)::value_t
{return children().back();}


auto dom::mixins::parentable_node::get_child_element_count() const -> decltype(this->child_element_count)::value_t
{return children().size();}


auto dom::mixins::parentable_node::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<parentable_node>{isolate}
            .inherit<dom_object>()
            .function("prepend", &parentable_node::prepend, UNSCOPABLE)
            .function("append", &parentable_node::append, UNSCOPABLE)
            .function("replaceChildren", &parentable_node::replace_children, UNSCOPABLE)
            .auto_wrap_objects();
    
    return std::move(conversion);
}
