#ifndef SBROWSER2_TREE_INTERNALS_HPP
#define SBROWSER2_TREE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class node;}
namespace dom::nodes {class text;}

namespace dom::detail::tree_internals
{
    // ancestors and descendants
    auto root(
            const nodes::node* node_a)
            -> nodes::node*;

    auto ancestors(
            const nodes::node* node_a)
            -> ranges::any_view<nodes::node*>;

    auto descendants(
            const nodes::node* node_a)
            -> ranges::any_view<nodes::node*>;
    
    // tree checks
    auto is_ancestor(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_descendant(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_sibling(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_preceding(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_following(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    // indexing and length of nodes
    auto index(
            const nodes::node* node_a)
            -> ext::number<ulong>;

    auto length(
            const nodes::node* node_a)
            -> ext::number<ulong>;

    // lists of nodes preceding or following another node
    template <typename T=nodes::node>
    auto all_following(
            const nodes::node* node_a)
            -> ranges::any_view<T*, ranges::category::sized | ranges::category::forward>;

    template <typename T=nodes::node>
    auto all_preceding(
            const nodes::node* node_a)
            -> ranges::any_view<T*, ranges::category::sized | ranges::category::forward>;

    template <typename T=nodes::node>
    auto all_following_siblings(
            const nodes::node* node_a)
            -> ranges::any_view<T*, ranges::category::sized | ranges::category::forward>;

    template <typename T=nodes::node>
    auto all_preceding_siblings(
            const nodes::node* node_a)
            -> ranges::any_view<T*, ranges::category::sized | ranges::category::forward>;

    // node type checks (used for filters)
    auto is_element_node(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_text_node(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_exclusive_text_node(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_document_type_node(
            const nodes::node* node_a)
            -> ext::boolean;

    // text node helpers
    auto contiguous_text_nodes(
            const nodes::node* node_a)
            -> ranges::any_view<nodes::text*>;

    auto descendant_text_nodes(
            const nodes::node* node_a)
            -> ranges::any_view<nodes::text*>;

    auto child_text_nodes(
            const nodes::node* node_a)
            -> ranges::any_view<nodes::text*>;

    auto descendant_text_content(
            const nodes::node* node_a)
            -> ext::string;

    auto child_text_content(
            const nodes::node* node_a)
            -> ext::string;

    // other general helper methods for nodes
    auto common_ancestor(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> nodes::node*;

    auto is_document_element(
            const nodes::node* node_a)
            -> ext::boolean;
}


#endif //SBROWSER2_TREE_INTERNALS_HPP
