#include "non_document_type_child_node.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"

#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"

#include <range/v3/algorithm/find.hpp>
#include <range/v3/view/slice.hpp>
#include <range/v3/view/subrange.hpp>


auto dom::mixins::non_document_type_child_node::get_previous_element_sibling() const
        -> nodes::element*
{
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) siblings = *base->parent_node()->child_nodes();
    decltype(auto) previous_siblings = ranges::subrange(siblings.begin(), ranges::find(siblings, base));
    return ranges::back(siblings | ranges::views::cast_all_to.operator()<nodes::element*>());
}


auto dom::mixins::non_document_type_child_node::get_next_element_sibling()
        const -> nodes::element*
{
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) siblings = *base->parent_node()->child_nodes();
    decltype(auto) previous_siblings = ranges::subrange(ranges::find(siblings, base), siblings.end());
    return ranges::front(siblings | ranges::views::cast_all_to.operator()<nodes::element*>());
}


auto dom::mixins::non_document_type_child_node::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<non_document_type_child_node>{isolate}
        .inherit<dom_object>()
        .property("previousElementSibling", &non_document_type_child_node::get_previous_element_sibling)
        .property("nextElementSibling", &non_document_type_child_node::get_next_element_sibling)
        .auto_wrap_objects();

    return std::move(conversion);
}
