#include "non_element_parent_node.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"

#include "dom/nodes/element.hpp"
#include "dom/detail/tree_internals.hpp"

#include <range/v3/view/filter.hpp>


auto dom::mixins::non_element_parent_node::get_element_by_id(
        const ext::string_view id)
        -> nodes::element*
{
    // cross cast this node to a Node, get the element descendant nodes, and filter them by their id; if the element is
    // not nullptr and the id matches then add it to the matches range; return teh first matching element, otherwise
    // nullptr
    const auto* const base = ext::cross_cast<const nodes::node*>(this);
    auto matches = detail::tree_internals::descendants(base)
            | ranges::views::cast_all_to<nodes::element*>()
            | ranges::views::filter([id](const nodes::element* const element) {return element && element->id() == id;});

    return *matches.begin(); // will be nullptr for empty list
}


auto dom::mixins::non_element_parent_node::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<non_element_parent_node>{isolate}
        .inherit<dom_object>()
        .function("getElementById", &non_element_parent_node::get_element_by_id)
        .auto_wrap_objects();
}
