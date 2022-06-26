#include "non_element_parent_node.hpp"

#include <ext/casting.hpp>
#include <ext/ranges.hpp>

#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>


auto dom::mixins::non_element_parent_node::get_element_by_id(
        ext::string_view id)
        -> nodes::element*
{
    // cross cast this node to a Node, get the element descendant nodes, and filter them by their id; if the element is
    // not nullptr and the id matches then add it to the matches range; return teh first matching element, otherwise
    // nullptr
    auto* base = ext::cross_cast<nodes::node*>(this);
    auto matches = detail::tree_internals::descendants(base)
            | ranges::views::cast_<nodes::element*>(node);})
            | ranges::views::filter([id](nodes::element* element) {return element && element->id() == id;});

    return !matches.empty() ? matches.front() : nullptr;
}


auto dom::mixins::non_element_parent_node::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<non_element_parent_node>{isolate}
        .inherit<web_apis::dom_object>()
        .function("getElementById", &non_element_parent_node::get_element_by_id)
        .auto_wrap_objects();
}
