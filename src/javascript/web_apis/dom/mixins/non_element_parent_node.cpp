#include "non_element_parent_node.hpp"
#include "non_element_parent_node_private.hpp"

#include "ext/casting.hpp"
#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/detail/tree_internals.hpp"

#include <range/v3/view/filter.hpp>


auto dom::mixins::non_element_parent_node::get_element_by_id(const ext::string_view id) -> nodes::element*
{
    // Cross cast this object to a Node, get the element descendant nodes, and filter them by their id (match against
    // the 'id' parameter); if the element is not nullptr and the ids match, then add the element to the matches range.
    // Rreturn the first matching element if there is one, otherwise nullptr.
    using enum ranges::filter_compare_t;
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    auto matches = detail::descendants(base)
            | ranges::views::cast<nodes::element*>
            | ranges::views::filter(ext::pointer_not_null)
            | ranges::views::filter_eq<EQ>(&nodes::element_private::id, id, ext::get_pimpl);

    return matches.empty() ? nullptr : matches.front();
}


auto dom::mixins::non_element_parent_node::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("getElementById", &non_element_parent_node::get_element_by_id)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
