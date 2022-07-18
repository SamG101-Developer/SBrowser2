#include "non_document_type_child_node.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"

#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"

#include <range/v3/algorithm/find.hpp>
#include <range/v3/view/slice.hpp>
#include <range/v3/view/subrange.hpp>


dom::mixins::non_document_type_child_node::non_document_type_child_node()
{
    bind_get(previous_element_sibling);
    bind_get(next_element_sibling);
}


auto dom::mixins::non_document_type_child_node::get_previous_element_sibling()
        const -> nodes::element*
{
    const auto* const base = ext::cross_cast<const nodes::node*>(this);
    const auto& siblings = *base->parent_node()->child_nodes();
    const auto previous_siblings = ranges::subrange(siblings.begin(), ranges::find(siblings, base));
    return ranges::end(siblings | ranges::views::cast_all_to<nodes::element*>());
}


auto dom::mixins::non_document_type_child_node::get_next_element_sibling()
        const -> nodes::element*
{
    const auto* const base = ext::cross_cast<const nodes::node*>(this);
    const auto& siblings = *base->parent_node()->child_nodes();
    const auto previous_siblings = ranges::subrange(ranges::find(siblings, base), siblings.end());
    return ranges::end(siblings | ranges::views::cast_all_to<nodes::element*>());
}
