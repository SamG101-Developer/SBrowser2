#ifndef SBROWSER2_TREE_INTERNALS_HPP
#define SBROWSER2_TREE_INTERNALS_HPP

#include <ext/boolean.hpp>
#include <ext/casting.hpp>
#include <ext/number.hpp>
#include <ext/string.hpp>
#include <ext/type_traits.hpp>
#include <ext/vector.hpp>

#include <web_apis/dom/nodes/attr.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/nodes/text.hpp>

#include <range/v3/to_container.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/set_algorithm.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/reverse.hpp>

namespace dom::nodes {class node;}
namespace dom::nodes {class text;}

namespace dom::detail::tree_internals
{
    // ancestors and descendants
    auto root(
            nodes::node* node_a)
            -> nodes::node*;

    auto ancestors(
            nodes::node* node_a)
            -> range_v3_view auto;

    auto descendants(
            nodes::node* node_a)
            -> range_v3_view auto;
    
    // tree checks
    auto is_ancestor(
            nodes::node* node_a,
            nodes::node* node_b)
            -> ext::boolean;

    auto is_descendant(
            nodes::node* node_a,
            nodes::node* node_b)
            -> ext::boolean;

    auto is_sibling(
            nodes::node* node_a,
            nodes::node* node_b)
            -> ext::boolean;

    auto is_preceding(
            nodes::node* node_a,
            nodes::node* node_b)
            -> ext::boolean;

    auto is_following(
            nodes::node* node_a,
            nodes::node* node_b)
            -> ext::boolean;

    // indexing and length of nodes
    auto index(
            nodes::node* node_a)
            -> ext::number<ulong>;

    auto length(
            nodes::node* node_a)
            -> ext::number<ulong>;

    // lists of nodes preceding or following another node
    template <typename T=nodes::node*>
    auto all_following(
            nodes::node* node_a)
            -> range_v3_view auto;

    template <typename T=nodes::node*>
    auto all_preceding(
            nodes::node* node_a)
            -> range_v3_view auto;

    template <typename T=nodes::node*>
    auto all_following_siblings(
            nodes::node* node_a)
            -> range_v3_view auto;

    template <typename T=nodes::node*>
    auto all_preceding_siblings(
            nodes::node* node_a)
            -> range_v3_view auto;

    // node type checks (used for filters)
    auto is_element_node(
            nodes::node* node_a)
            -> ext::boolean;

    auto is_text_node(
            nodes::node* node_a)
            -> ext::boolean;

    auto is_exclusive_text_node(
            nodes::node* node_a)
            -> ext::boolean;

    auto is_document_type_node(
            nodes::node* node_a)
            -> ext::boolean;

    // text node helpers
    auto contiguous_text_nodes(
            nodes::node* node_a)
            -> range_v3_view auto;

    auto descendant_text_nodes(
            nodes::node* node_a)
            -> range_v3_view auto;

    auto child_text_nodes(
            nodes::node* node_a)
            -> range_v3_view auto;

    auto descendant_text_content(
            nodes::node* node_a)
            -> ext::string;

    auto child_text_content(
            nodes::node* node_a)
            -> ext::string;

    // other general helper methods for nodes
    auto common_ancestor(
            nodes::node* node_a,
            nodes::node* node_b)
            -> nodes::node*;

    auto is_document_element(
            nodes::node* node_a)
            -> ext::boolean;
}


auto dom::detail::tree_internals::root(nodes::node* node_a) -> nodes::node*
{
    // return the topmost ancestor, or nullptr if there is no node
    return not node_a ? nullptr : node_a->parent_node() ? root(node_a->parent_node()) : node_a;
}


auto dom::detail::tree_internals::ancestors(nodes::node* node_a) -> range_v3_view auto
{
    // iterate up through the parent_node attributes, until the root is reached, appending each element
    ext::vector<nodes::node*> ancestor_nodes {node_a};
    while ((node_a = node_a->parent_node())) ancestor_nodes.push_back(node_a);
    return ranges::ref_view{ancestor_nodes};
}


auto dom::detail::tree_internals::descendants(nodes::node* node_a) -> range_v3_view auto
{
    // iterate though the children, appending each child and the child of that child, until the last child is checked
    ext::vector<nodes::node*> descendant_nodes {node_a};
    for (const auto& child: descendant_nodes) descendant_nodes.extend(ranges::find(descendant_nodes, child), *child->child_nodes());
    return ranges::ref_view(descendant_nodes);
}


auto dom::detail::tree_internals::is_ancestor(nodes::node* node_a, nodes::node* node_b) -> ext::boolean
{
    // 'node_a' is an ancestor of 'node_b' if it is in the ancestor() list for 'node_b'
    if (!node_a || !node_b) return false;
    auto ancestors_of_b = ancestors(node_b);
    return ranges::contains(ancestors_of_b, node_a);
}


auto dom::detail::tree_internals::is_descendant(nodes::node* node_a, nodes::node* node_b) -> ext::boolean
{
    // 'node_a' is a descendant of 'node_b' if 'node_b' is an ancestor of 'node_a' (faster than generating descendants)
    return is_ancestor(node_b, node_a);
}


auto dom::detail::tree_internals::is_sibling(nodes::node* node_a, nodes::node* node_b) -> ext::boolean
{
    // 'node_a' is a sibling of 'node_b' if they have the same 'parent_node'
    return node_a->parent_node == node_b->parent_node;
}


auto dom::detail::tree_internals::is_preceding(nodes::node* node_a, nodes::node* node_b) -> ext::boolean
{
    // 'node_a' precedes 'node_b' if its index is lower
    return index(node_a) < index(node_b);
}


auto dom::detail::tree_internals::is_following(nodes::node* node_a, nodes::node* node_b) -> ext::boolean
{
    // 'node_a' follows 'node_b' if its index is higher
    return index(node_a) > index(node_b);
}


auto dom::detail::tree_internals::index(nodes::node* node_a) -> ext::number<ulong>
{
    auto descendant_nodes = descendants(root(node_a));
    auto where_iterator   = ranges::find(descendant_nodes, node_a);
    auto where_index      = std::distance(descendant_nodes.begin(), where_iterator);
    return where_index;
}


auto dom::detail::tree_internals::length(nodes::node* node_a) -> ext::number<ulong>
{
    if (!node_a || ext::multi_cast<nodes::attr*, nodes::document_type*>(node_a)) return 0;
    else if (ext::multi_cast<nodes::character_data*>(node_a)) return dynamic_cast<nodes::character_data*>(node_a)->length();
    else return node_a->child_nodes->size();
}


template <typename T>
auto dom::detail::tree_internals::all_following(nodes::node* node_a) -> range_v3_view auto
{
    auto descendant_nodes = descendants(node_a);
    return descendant_nodes
           | ranges::views::transform([](nodes::node* descendant) {return dynamic_cast<T*>(descendant);})
           | ranges::views::filter([](T* descendant) -> bool {return descendant;})
           | ranges::views::filter([index_a = index(node_a)](T* descendant) {return index(descendant) < index_a;});
}


template <typename T>
auto dom::detail::tree_internals::all_preceding(nodes::node* node_a) -> range_v3_view auto
{
    auto descendant_nodes = descendants(node_a);
    return descendant_nodes
           | ranges::views::transform([](nodes::node* descendant) {return dynamic_cast<T*>(descendant);})
           | ranges::views::filter([](T* descendant) -> bool {return descendant;})
           | ranges::views::filter([index_a = index(node_a)](T* descendant) {return index(descendant) > index_a;});
}


template <typename T>
auto dom::detail::tree_internals::all_preceding_siblings(nodes::node* node_a) -> range_v3_view auto
{
    auto sibling_nodes = node_a->parent_node->child_nodes();
    return *sibling_nodes
           | ranges::views::transform([](nodes::node* descendant) {return dynamic_cast<T*>(descendant);})
           | ranges::views::filter([](T* sibling) -> bool {return sibling;})
           | ranges::views::filter([index_a = ranges::find(*sibling_nodes, node_a), &sibling_nodes](T* sibling) {return ranges::find(*sibling_nodes, sibling) < index_a;});
}


template <typename T>
auto dom::detail::tree_internals::all_following_siblings(nodes::node* node_a) -> range_v3_view auto
{
    auto sibling_nodes = node_a->parent_node->child_nodes();
    return *sibling_nodes
           | ranges::views::transform([](nodes::node* descendant) {return dynamic_cast<T*>(descendant);})
           | ranges::views::filter([](T* sibling) -> bool {return sibling;})
           | ranges::views::filter([index_a = ranges::find(*sibling_nodes, node_a), &sibling_nodes](T* sibling) {return ranges::find(*sibling_nodes, sibling) > index_a;});
}


auto dom::detail::tree_internals::is_element_node(nodes::node* node_a) -> ext::boolean
{
    return dynamic_cast<nodes::element*>(node_a);
}


auto dom::detail::tree_internals::is_text_node(nodes::node* node_a) -> ext::boolean
{
    return dynamic_cast<nodes::character_data*>(node_a);
}


auto dom::detail::tree_internals::is_exclusive_text_node(nodes::node* node_a) -> ext::boolean
{
    return dynamic_cast<nodes::text*>(node_a);
}


auto dom::detail::tree_internals::is_document_type_node(nodes::node* node_a) -> ext::boolean
{
    return dynamic_cast<nodes::document_type*>(node_a);
}


auto dom::detail::tree_internals::contiguous_text_nodes(nodes::node* node_a) -> range_v3_view auto
{
    auto sibling_nodes = node_a->parent_node->child_nodes();

    // current text node as a range
    auto current_text_node = *sibling_nodes
            | ranges::views::filter([&node_a](nodes::node* sibling) {return sibling == node_a;});

    // previous consecutive text nodes as a range (adjacent to 'node_a')
    auto previous_consecutive_text_nodes = *sibling_nodes | ranges::views::reverse
            | ranges::views::drop_while([&node_a](nodes::node* sibling) {return sibling != node_a;})
            | ranges::views::transform([](nodes::node* sibling) {return dynamic_cast<nodes::text*>(sibling);})
            | ranges::views::take_while([](nodes::text* sibling_text_node) -> bool {return sibling_text_node;})
            | ranges::views::reverse;

    // next consecutive text nodes as a range (adjacent to 'node_a')
    auto next_consecutive_text_nodes = *sibling_nodes
            | ranges::views::drop_while([&node_a](nodes::node* sibling) {return sibling != node_a;})
            | ranges::views::transform([](nodes::node* sibling) {return dynamic_cast<nodes::text*>(sibling);})
            | ranges::views::take_while([](nodes::text* sibling_text_node) -> bool {return sibling_text_node;});

    return ranges::views::concat(previous_consecutive_text_nodes, current_text_node, next_consecutive_text_nodes);
}


auto dom::detail::tree_internals::descendant_text_nodes(nodes::node* node_a) -> range_v3_view auto
{
    auto descendant_nodes = descendants(node_a);
    return descendant_nodes
            | ranges::views::transform([](nodes::node* descendant) {return dynamic_cast<nodes::text*>(descendant);})
            | ranges::views::filter([](nodes::text* text_node) -> bool {return text_node;});
}


auto dom::detail::tree_internals::child_text_nodes(nodes::node* node_a) -> range_v3_view auto
{
    auto child_nodes = node_a->parent_node->child_nodes();
    return *child_nodes
            | ranges::views::transform([](nodes::node* descendant) {return dynamic_cast<nodes::text*>(descendant);})
            | ranges::views::filter([](nodes::text* text_node) -> bool {return text_node;});
}


auto dom::detail::tree_internals::descendant_text_content(nodes::node* node_a) -> ext::string
{
    return descendant_text_nodes(node_a)
            | ranges::views::transform([](nodes::text* descendant_text_node) {return descendant_text_node->data();})
            | ranges::to<ext::string>();
}


auto dom::detail::tree_internals::child_text_content(nodes::node* node_a) -> ext::string
{
    return child_text_nodes(node_a)
            | ranges::views::transform([](nodes::text* child_text_node) {return child_text_node->data();})
            | ranges::to<ext::string>();
}


auto dom::detail::tree_internals::common_ancestor(nodes::node* node_a, nodes::node* node_b) -> nodes::node*
{
    auto common_ancestor_nodes = ranges::views::set_intersection(ancestors(node_a), ancestors(node_b));
    return common_ancestor_nodes.front();
}


auto dom::detail::tree_internals::is_document_element(nodes::node* node_a) -> ext::boolean
{
    return is_element_node(node_a) && dynamic_cast<nodes::document*>(node_a->parent_node());
}



#endif //SBROWSER2_TREE_INTERNALS_HPP
