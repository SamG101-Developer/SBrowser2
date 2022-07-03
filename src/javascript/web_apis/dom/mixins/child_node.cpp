#include "child_node.hpp"

#include <ext/casting.hpp>

#include <dom/detail/customization_internals.hpp>
#include <dom/detail/mutation_internals.hpp>
#include <dom/detail/node_internals.hpp>
#include <dom/detail/tree_internals.hpp>
#include <range/v3/view/set_algorithm.hpp>


auto dom::mixins::child_node::before(
        type_in<nodes::node*, ext::string> auto&&... nodes)
        -> void
{
    ce_reactions_method_def
        // get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to insert nodes into a nullptr parent
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* parent = base->parent_node();
        return_if(!parent);

        // the 'viable_previous_siblings' are all the preceding siblings of 'node' that aren't in 'nodes' - this is the
        // set difference. convert the 'nodes' into a single Node
        auto viable_previous_siblings = detail::tree_internals::all_preceding_siblings(base)
                | ranges::views::set_difference(std::forward<decltype(nodes)>(nodes)...);

        auto* viable_previous_sibling = viable_previous_siblings.front();
        auto* node = detail::node_internals::convert_nodes_into_node(base->owner_document(), std::forward<decltype(nodes)>(nodes)...);

        // if 'viable_previous_sibling' is nullptr, adjust it to be the 'parent''s first child, so that the 'node' be
        // inserted as the first child for the 'parent'; otherwise set it to its next sibling, so 'node' is inserted
        // into the correct place
        viable_previous_sibling = !viable_previous_sibling ? parent->first_child() : viable_previous_sibling->next_sibling();
        detail::mutation_internals::pre_insert(node, parent, viable_previous_sibling);
    ce_reactions_method_exe
}


auto dom::mixins::child_node::after(
        type_in<nodes::node*, ext::string> auto&&... nodes)
        -> void
{
    ce_reactions_method_def
        // get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to insert nodes into a nullptr parent
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* parent = base->parent_node();
        return_if(!parent);

        // the 'viable_next_siblings' are all the following siblings of 'node' that aren't in 'nodes' - this is the set
        // difference. convert the 'nodes' into a single Node
        auto viable_next_siblings = detail::tree_internals::all_following_siblings(base)
                | ranges::views::set_difference(std::forward<decltype(nodes)>(nodes)...);

        auto* viable_next_sibling = viable_next_siblings.front();
        auto* node = detail::node_internals::convert_nodes_into_node(base->owner_document(), std::forward<decltype(nodes)>(nodes)...);

        // the 'viable_next_sibling' doesn't need adjusting, because if it nullptr, then the insertion algorithm will
        // detect the iterator as ...::end(), meaning that the 'node' will get appended, so 'node' is inserted into the
        // correct place anyway
        detail::mutation_internals::pre_insert(node, parent, viable_next_sibling);
    ce_reactions_method_exe
}


auto dom::mixins::child_node::replace_with(
        type_in<nodes::node*, ext::string> auto&& ...nodes)
        -> void
{
    ce_reactions_method_def
        // get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to replace nodes into a nullptr parent
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* parent = base->parent_node();
        return_if(!parent);

        // convert the 'nodes' into a single Node
        auto* node = detail::node_internals::convert_nodes_into_node(base->owner_document(), std::forward<decltype(nodes)>(nodes)...);

        // TODO : not sure how this statement would ever be false
        // if the 'parent' matches the node's parent, replace this node with 'node', otherwise insert 'node' into
        // 'parent', before the determined 'viable_next_sibling'
        if (base->parent_node() == parent)
            detail::mutation_internals::replace(base, parent, node);
        else
        {
            // the 'viable_next_siblings' are all the following siblings of 'node' that aren't in 'nodes' - this is the
            // set difference
            auto viable_next_siblings = detail::tree_internals::all_following_siblings(base)
                    | ranges::views::set_difference(std::forward<decltype(nodes)>(nodes)...);

            auto* viable_next_sibling = viable_next_siblings.front();
            detail::mutation_internals::pre_insert(node, parent, viable_next_sibling);
        }
    ce_reactions_method_exe
}


auto dom::mixins::child_node::remove()
        -> void
{
    ce_reactions_method_def
        // get the node* cross-cast of 'this', and store the parent node, returning early if the parent is nullptr; it's
        // not possible to remove nodes into a nullptr parent
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* parent = base->parent_node();
        return_if(!parent);

        // remove this node from the DOM tree
        detail::mutation_internals::remove(base);
    ce_reactions_method_exe
}


auto dom::mixins::child_node::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<child_node>{isolate}
        .inherit<web_apis::dom_object>()
        .function("before", &child_node::before, v8::DontEnum)
        .function("append", &child_node::after, v8::DontEnum)
        .function("replaceWith", &child_node::replace_with, v8::DontEnum)
        .function("remove", &child_node::remove, v8::DontEnum)
        .auto_wrap_objects();
}
