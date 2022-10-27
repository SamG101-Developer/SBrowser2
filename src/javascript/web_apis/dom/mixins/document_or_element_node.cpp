#include "document_or_element_node.hpp"
#include "document_or_element_node_private.hpp"

#include "ext/casting.hpp"
#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"

#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/algorithm/all_of.hpp>


auto dom::mixins::document_or_element_node::get_elements_by_class_name(
        const ext::string_view class_names)
        const -> ranges::any_view<nodes::element*>
{
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);

    // Split the class names of a Node by spaces, and determine 'lower', which causes everything to be compared in
    // lowercase; if 'lower' is true, then convert the 'class_names' list into lowercase strings.
    auto lower = base->d_func()->node_document->d_func()->mode == u8"quirks";
    auto class_list = class_names
            | ranges::views::split_string(' ')
            | ranges::views::transform_if(lower, ranges::actions::lowercase);

    // The 'match_callback' checks if all the class list items from an element are contained in the list that was passed
    // into the function as a parameter. the element's class list is converted into lowercase if 'lower' is set.
    auto match_callback = [&class_list, lower = lower] (const nodes::element* const element) mutable
    {
        auto this_class_list = element->d_func()->class_ | ranges::views::transform_if(lower, ranges::actions::lowercase);
        return ranges::contains_all(class_list, this_class_list);
    };

    // Filter the elements by applying the 'match_callback' onto each Element; if all the Element's class list items are
    // in the 'class_names' parameter, then keep the element, otherwise discard it.
    auto matches = detail::descendants(base)
            | ranges::views::cast_all_to<nodes::element*>()
            | ranges::views::filter(match_callback);

    return matches;
}


auto dom::mixins::document_or_element_node::get_elements_by_tag_name(
        ext::string_view qualified_name)
        const -> ranges::any_view<nodes::element*>
{
    // Cross cast this node to a Node.
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);

    // Determine 'lower', which causes everything to be compared in lowercase; if 'lower' is true, then convert the
    // 'qualified_name' into a lowercase string.
    auto lower = base->d_func()->node_document->d_func()->mode == u8"quirks";
    auto that_qualified_name = ext::string{qualified_name};
    if (lower) that_qualified_name |= ranges::actions::lowercase();

    // The 'match_callback' checks if the qualified name of en element matches the qualified name that was passed into
    // the function as parameter. the element's qualified name is concerned into lowercase is 'lower' is set.
    auto match_callback = [&that_qualified_name, lower](const nodes::element* const element)
    {
        auto this_qualified_name = detail::qualified_name(element);
        if (lower) this_qualified_name |= ranges::actions::lowercase();
        return this_qualified_name == u8"*" || this_qualified_name == that_qualified_name;
    };

    // Filter the elements by applying the 'match_callback' onto each Element; if the Element's qualified name equals
    // the 'qualified_name' parameter, then keep the element, otherwise discard it.
    using f_t = ext::function<bool(nodes::element*)>;
    auto matches = detail::descendants(base)
            | ranges::views::cast_all_to<nodes::element*>()
            | ranges::views::filter(match_callback);

    return matches;
}


auto dom::mixins::document_or_element_node::get_elements_by_tag_name_ns(
        const ext::string_view namespace_,
        const ext::string_view local_name)
        const -> ranges::any_view<nodes::element*>
{
    // Cross cast this node to a Node.
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);

    // The 'match_callback' checks if the 'namespace_' and 'local_name' of an element matches the namespace and local
    // name that were passed into the function as parameters. no html qualification is required for lowercase
    // conversion.
    auto match_callback = [&namespace_, &local_name](const nodes::element* const element)
    {
        auto this_namespace = element->d_func()->namespace_;
        auto this_local_name = element->d_func()->local_name;
        return (this_namespace == u8"*" || this_namespace == namespace_)
                && (this_local_name == u8"*" || this_local_name == local_name);
    };

    // Filter the elements by applying the 'match_callback' onto each Element; if the Element's namespace and local name
    // equal the 'namespace_' and 'local_name' parameters, then keep the element, otherwise discard it.
    auto matches = detail::descendants(base)
            | ranges::views::cast_all_to<nodes::element*>()
            | ranges::views::filter(match_callback);

    return matches;
}


auto dom::mixins::document_or_element_node::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document_or_element_node>{isolate}
        .inherit<dom_object>()
        .function("getElementsByClassName", &document_or_element_node::get_elements_by_class_name)
        .function("getElementsByTagName", &document_or_element_node::get_elements_by_tag_name)
        .function("getElementsByTagNameNS", &document_or_element_node::get_elements_by_tag_name_ns)
        .auto_wrap_objects();

    return std::move(conversion);
}
