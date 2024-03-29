module;
#include "ext/macros/custom_operator.hpp"

#include <range/v3/range/operations.hpp>
#include <range/v3/view/set_algorithm.hpp>


module apis.dom.mixins.child_node;
import apis.dom.node;

import ext.core;


template <ext::type_is<dom::nodes::node*, ext::string> ...Args>
auto dom::mixins::child_node::before(Args&&... nodes) -> nodes::node*
{
    _CE_REACTIONS_METHOD_DEF
        // Get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to insert nodes into a nullptr parent.
        decltype(auto) base = ext::cross_cast<const node*>(this);
        decltype(auto) parent = base->d_func()->parent_node.get();
        return_if(!parent) ext::nullptr_cast<nodes::node*>();

        // The 'viable_previous_siblings' are all the preceding siblings of 'node' that aren't in 'nodes' - this is the
        // set difference. convert the 'nodes' into a single Node.
        decltype(auto) viable_previous_siblings = detail::all_preceding_siblings(base)
                | ranges::views::set_difference(std::forward<Args>(nodes)...);

        decltype(auto) viable_previous_sibling = viable_previous_siblings.front();
        decltype(auto) node = detail::convert_nodes_into_node(base->d_func()->node_document, std::forward<Args>(nodes)...);

        // If 'viable_previous_sibling' is nullptr, adjust it to be the 'parent''s first child, so that the 'node' be
        // inserted as the first child for the 'parent'; otherwise set it to its next sibling, so 'node' is inserted
        // into the correct place.
        viable_previous_sibling = !viable_previous_sibling ? parent->d_func()->first_child() : viable_previous_sibling->d_func()->next_sibling();
        detail::pre_insert(node, parent, viable_previous_sibling);

        return node;
    _CE_REACTIONS_METHOD_EXE
}


template <ext::type_is<dom::nodes::node*, ext::string> ...Args>
auto dom::mixins::child_node::after(Args&&... nodes) -> nodes::node*
{
    _CE_REACTIONS_METHOD_DEF
        // Get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to insert nodes into a nullptr parent.
        decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
        decltype(auto) parent = base->d_func()->parent_node.get();
        return_if(!parent) ext::nullptr_cast<nodes::node*>();

        // The 'viable_next_siblings' are all the following siblings of 'node' that aren't in 'nodes' - this is the set
        // difference. convert the 'nodes' into a single Node.
        decltype(auto) viable_next_siblings = detail::all_following_siblings(base)
                | ranges::views::set_difference(std::forward<T>(nodes)...);

        decltype(auto) viable_next_sibling = viable_next_siblings.front();
        decltype(auto) node = detail::convert_nodes_into_node(base->d_func()->node_document, std::forward<T>(nodes)...);

        // The 'viable_next_sibling' doesn't need adjusting, because if it nullptr, then the insertion algorithm will
        // detect the iterator as ...::end(), meaning that the 'node' will get appended, so 'node' is inserted into the
        // correct place anyway.
        detail::pre_insert(node, parent, viable_next_sibling);

        return node;
    _CE_REACTIONS_METHOD_EXE
}


template <ext::type_is<dom::nodes::node*, ext::string> ...Args>
auto dom::mixins::child_node::replace_with(Args&& ...nodes) -> nodes::node*
{
    _CE_REACTIONS_METHOD_DEF
        // Get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to replace nodes into a nullptr parent.
        decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
        decltype(auto) parent = base->d_func()->parent_node.get();
        return_if(!parent) ext::nullptr_cast<nodes::node*>();

        // Convert the 'nodes' into a single Node.
        decltype(auto) node = detail::convert_nodes_into_node(base->d_func()->node_document, std::forward<T>(nodes)...);
        
        // If the 'parent' matches the node's parent, replace this node with 'node', otherwise insert 'node' into
        // 'parent', before the determined 'viable_next_sibling'.
        if (base->d_func()->parent_node.get() == parent)
            detail::replace(base, parent, node);
        else
        {
            // The 'viable_next_siblings' are all the following siblings of 'node' that aren't in 'nodes' - this is the
            // set difference.
            decltype(auto) next_siblings = detail::all_following_siblings(base);
            decltype(auto) viable_next_sibling = ranges::front(next_siblings | ranges::views::set_difference(std::forward<T>(nodes)...));

            detail::pre_insert(node, parent, viable_next_sibling);
        }

        return node;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::mixins::child_node::remove() -> nodes::node*
{
    _CE_REACTIONS_METHOD_DEF
        // Get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to remove nodes into a nullptr parent.
        decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
        decltype(auto) parent = base->d_func()->parent_node.get();
        return_if (!parent) ext::nullptr_cast<nodes::node*>();

        // Remove this node from the DOM tree.
        detail::remove(base);

        return ext::nullptr_cast<nodes::node*>();
    _CE_REACTIONS_METHOD_EXE
}


auto dom::mixins::child_node::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("before", &child_node::before, UNSCOPABLE)
        .function("append", &child_node::after, UNSCOPABLE)
        .function("replaceWith", &child_node::replace_with, UNSCOPABLE)
        .function("remove", &child_node::remove, UNSCOPABLE)
        .auto_wrap_objects();
    
    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
