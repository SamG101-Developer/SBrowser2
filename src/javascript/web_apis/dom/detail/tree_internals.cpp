#include "tree_internals.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"

#include "dom/nodes/attr.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_type.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/text.hpp"

#include <range/v3/view/concat.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/set_algorithm.hpp>
#include <range/v3/view/take_while.hpp>


auto dom::detail::root(
        const nodes::node* const node_a)
        -> nodes::node*
{
    // return the topmost ancestor, or nullptr if there is no node
    return !node_a ? nullptr : node_a->d_func()->parent_node ? root(node_a->d_func()->parent_node) : node_a;
}


auto dom::detail::ancestors(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::node*>
{
    // iterate up through the parent_node attributes, until the root is reached, appending each element
    // TODO: range based solution (live tree)
}


auto dom::detail::descendants(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::node*>
{
    // iterate though the children, appending each child and the child of that child, until the last child is checked
    // TODO: range based solution (live tree)
}


auto dom::detail::is_ancestor(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' is an ancestor of 'node_b' if it is in the ancestor() list for 'node_b'
    return_if (!node_a || !node_b) false;
    auto ancestors_of_b = ancestors(node_b);
    return ranges::contains(ancestors_of_b, node_a);
}


auto dom::detail::is_descendant(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' is a descendant of 'node_b' if 'node_b' is an ancestor of 'node_a' (faster than generating descendants)
    return is_ancestor(node_b, node_a);
}


auto dom::detail::is_sibling(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' is a sibling of 'node_b' if they have the same 'parent_node'
    return node_a->d_func()->parent_node == node_b->d_func()->parent_node;
}


auto dom::detail::is_preceding(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' precedes 'node_b' if its index is lower
    return index(node_a) < index(node_b);
}


auto dom::detail::is_following(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' follows 'node_b' if its index is higher
    return index(node_a) > index(node_b);
}


auto dom::detail::index(
        const nodes::node* const node_a)
        -> ext::number<ulong>
{
    auto descendant_nodes = descendants(root(node_a));
    auto where_iterator   = ranges::find(descendant_nodes, node_a);
    auto where_index      = std::distance(descendant_nodes.begin(), where_iterator);
    return where_index;
}


auto dom::detail::length(
        const nodes::node* const node_a)
        -> ext::number<ulong>
{
    if (!node_a || ext::multi_cast<const nodes::attr*, const nodes::document_type*>(node_a)) return 0;
    else if (auto* const character_data_a = dynamic_cast<const nodes::character_data*>(node_a)) return character_data_a->d_func()->length;
    else return node_a->d_func()->child_nodes.size();
}


auto dom::detail::first_child(
        const nodes::node* node)
        -> nodes::node*
{
    return node->d_func()->child_nodes.front().get();
}


auto dom::detail::last_child(
        const nodes::node* node)
        -> nodes::node*
{
    return node->d_func()->child_nodes.back().get();
}


auto dom::detail::previous_sibling(
        const nodes::node* node)
        -> nodes::node*
{
    decltype(auto) siblings = node->d_func()->parent_node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<nodes::node>::get);
    decltype(auto) this_node_iter = ranges::find(siblings, node);
    return this_node_iter != siblings.begin() ? *(this_node_iter - 1) : nullptr;
}


auto dom::detail::next_sibling(
        const nodes::node* node)
        -> nodes::node*
{
    decltype(auto) siblings = node->d_func()->parent_node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<nodes::node>::get);
    decltype(auto) this_node_iter = ranges::find(siblings, node);
    return (this_node_iter + 1 != siblings.end()) ? *(this_node_iter + 1) : nullptr;
}


template <typename T>
auto dom::detail::all_following(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::node*>
{
    auto descendant_nodes = descendants(node_a);
    return descendant_nodes
           | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<T*>()
           | ranges::views::filter([index_a = index(node_a)](T* descendant) {return index(descendant) < index_a;});
}


template <typename T>
auto dom::detail::all_preceding(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::node*>
{
    auto descendant_nodes = descendants(node_a);
    return descendant_nodes
           | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<T*>()
           | ranges::views::filter([index_a = index(node_a)](T* descendant) {return index(descendant) > index_a;});
}


template <typename T>
auto dom::detail::all_preceding_siblings(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::node*>
{
    auto sibling_nodes = node_a->d_func()->parent_node->child_nodes;
    return sibling_nodes
           | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<T*>()
           | ranges::views::filter([index_a = ranges::find(sibling_nodes, node_a), &sibling_nodes](T* sibling) {return ranges::find(sibling_nodes, sibling) < index_a;});
}


template <typename T>
auto dom::detail::all_following_siblings(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::node*>
{
    auto sibling_nodes = node_a->d_func()->parent_node->child_nodes();
    return sibling_nodes
           | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<T*>()
           | ranges::views::filter([index_a = ranges::find(sibling_nodes, node_a), &sibling_nodes](T* sibling) {return ranges::find(sibling_nodes, sibling) > index_a;});
}


auto dom::detail::is_element_node(
        const nodes::node* const node_a)
        -> ext::boolean
{
    return dynamic_cast<const nodes::element*>(node_a);
}


auto dom::detail::is_text_node(
        const nodes::node* const node_a)
        -> ext::boolean
{
    return dynamic_cast<const nodes::character_data*>(node_a);
}


auto dom::detail::is_exclusive_text_node(
        const nodes::node* const node_a)
        -> ext::boolean
{
    return dynamic_cast<const nodes::text*>(node_a);
}


auto dom::detail::is_document_type_node(
        const nodes::node* const node_a)
        -> ext::boolean
{
    return dynamic_cast<const nodes::document_type*>(node_a);
}


auto dom::detail::contiguous_text_nodes(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::text*>
{
    decltype(auto) sibling_nodes = node_a->d_func()->parent_node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<nodes::node>::get);

    // current text node as a range
    auto current_text_node = sibling_nodes
            | ranges::views::filter([&node_a](const nodes::node* const sibling) {return sibling == node_a;});

    // previous consecutive text nodes as a range (adjacent to 'node_a')
    auto previous_consecutive_text_nodes = sibling_nodes | ranges::views::reverse
            | ranges::views::drop_while([&node_a](const nodes::node* const sibling) {return sibling != node_a;})
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::text*>(false)
            | ranges::views::take_while([](const nodes::text* const sibling_text_node) -> bool {return sibling_text_node;})
            | ranges::views::reverse;

    // next consecutive text nodes as a range (adjacent to 'node_a')
    auto next_consecutive_text_nodes = sibling_nodes
            | ranges::views::drop_while([&node_a](const nodes::node* const sibling) {return sibling != node_a;})
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::text*>(false)
            | ranges::views::take_while([](const nodes::text* const sibling_text_node) -> bool {return sibling_text_node;});

    return ranges::views::concat(previous_consecutive_text_nodes, current_text_node, next_consecutive_text_nodes);
}


auto dom::detail::descendant_text_nodes(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::text*>
{
    const auto descendant_nodes = descendants(node_a);
    return descendant_nodes | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::text*>();
}


auto dom::detail::child_text_nodes(
        const nodes::node* const node_a)
        -> ranges::any_helpful_view<nodes::text*>
{
    return node_a->d_func()->parent_node->d_func()->child_nodes
            | ranges::views::transform(&std::unique_ptr<nodes::node>::get)
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<nodes::text*>();
}


auto dom::detail::descendant_text_content(
        const nodes::node* const node_a)
        -> ext::string
{
    return descendant_text_nodes(node_a)
           | ranges::views::transform([](auto* descendant_text_node) {return descendant_text_node->d_func()->data;})
           | ranges::to<ext::string>();
}


auto dom::detail::child_text_content(
        const nodes::node* const node_a)
        -> ext::string
{
    return child_text_nodes(node_a)
           | ranges::views::transform([](auto* child_text_node) {return child_text_node->d_func()->data;})
           | ranges::to<ext::string>();
}


auto dom::detail::common_ancestor(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> nodes::node*
{
    auto common_ancestor_nodes = ranges::views::set_intersection(ancestors(node_a), ancestors(node_b));
    return common_ancestor_nodes.front();
}


auto dom::detail::is_document_element(
        const nodes::node* const node_a)
        -> ext::boolean
{
    return is_element_node(node_a) && dynamic_cast<nodes::document*>(node_a->d_func()->parent_node);
}
