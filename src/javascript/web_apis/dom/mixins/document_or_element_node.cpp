#include "document_or_element_node.hpp"

#include <regex>
#include <ext/functors.hpp>
#include <ext/ranges.hpp>

#include <ext/casting.hpp>
#include <ext/ranges.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
#include <web_apis/dom/nodes/element.hpp>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/algorithm/all_of.hpp>


auto dom::mixins::document_or_element_node::get_elements_by_class_name(
        ext::string class_names)
        -> range_v3_view auto
{
    auto* base = ext::cross_cast<nodes::node*>(this);

    // split the class names of a Node by spaces, and determine 'lower', which causes everything to be compared in
    // lowercase; if 'lower' is true, then convert the 'class_names' list into lowercase strings
    auto lower = base->owner_document->m_mode == "quirks";
    auto class_list = class_names | ranges::views::split_string(" ");
    class_list |= ranges::views::transform([lower](ext::string item) {if (lower) item |= ranges::views::lowercase();});

    // the 'match_callback' checks if all the class list items from an element are contained in the list that was passed
    // into the function as a parameter. the element's class list is converted into lowercase if 'lower' is set
    auto match_callback = [&class_list, lower](nodes::element* element)
    {
        ext::string_vector& this_class_list = *element->class_list();
        this_class_list |= ranges::views::transform([lower](ext::string item) {if (lower) item |= ranges::views::lowercase();});
        return ranges::contains_all(class_list, this_class_list);
    };

    // filter the elements by applying the 'match_callback' onto each Element; if all the Element's class list items are
    // in the 'class_names' parameter, then keep the element, otherwise discard it
    auto matches = detail::tree_internals::descendants(base)
            | ranges::views::cast_all_to<nodes::element>()
            | ranges::views::filter(match_callback);

    return matches;
}


auto dom::mixins::document_or_element_node::get_elements_by_tag_name(
        ext::string qualified_name)
        -> range_v3_view auto
{
    // cross cast this node to a Node
    auto* base = ext::cross_cast<nodes::node*>(this);

    // determine 'lower', which causes everything to be compared in lowercase; if 'lower' is true, then convert the
    // 'qualified_name' into a lowercase string
    auto lower = base->owner_document->m_mode == "quirks";
    if (lower) qualified_name |= ranges::views::lowercase();

    // the 'match_callback' checks if the qualified name of en element matches the qualified name that was passed into
    // the function as parameter. the element's qualified name is concerned into lowercase is 'lower' is set
    auto match_callback = [&qualified_name, lower](nodes::element* element)
    {
        auto this_qualified_name = element->qualified_name();
        if (lower) this_qualified_name | ranges::views::lowercase();
        return this_qualified_name == "*" || this_qualified_name == qualified_name;
    };

    // filter the elements by applying the 'match_callback' onto each Element; if the Element's qualified name equals
    // the 'qualified_name' parameter, then keep the element, otherwise discard it
    using f_t = std::function<bool(nodes::element*)>;
    auto matches = detail::tree_internals::descendants(base)
            | ranges::views::cast_all_to<nodes::element>()
            | ranges::views::filter(match_callback);

    return matches;
}


auto dom::mixins::document_or_element_node::get_elements_by_tag_name_ns(
        ext::string namespace_,
        ext::string local_name)
        -> range_v3_view auto
{
    // cross cast this node to a Node
    auto* base = ext::cross_cast<nodes::node*>(this);

    // the 'match_callback' checks if the 'namespace_' and 'local_name' of an element matches the namespace and local
    // name that were passed into the function as parameters. no html qualification is required for lowercase conversion
    auto match_callback = [&namespace_, &local_name](nodes::element* element)
    {
        auto this_namespace = element->namespace_uri();
        auto this_local_name = element->local_name();
        return (this_namespace == "*" || this_namespace == namespace_)
                && (this_local_name == "*" || this_local_name == local_name);
    };

    // filter the elements by applying the 'match_callback' onto each Element; if the Element's namespace and local name
    // equal the 'namespace_' and 'local_name' parameters, then keep the element, otherwise discard it
    auto matches = detail::tree_internals::descendants(base)
            | ranges::views::cast_all_to<nodes::element>()
            | ranges::views::filter(match_callback);

    return matches;
}


auto dom::mixins::document_or_element_node::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<document_or_element_node>{isolate}
        .inherit<web_apis::dom_object>()
        .function("getElementsByClassName", &document_or_element_node::get_elements_by_class_name)
        .function("getElementsByTagName", &document_or_element_node::get_elements_by_tag_name)
        .function("getElementsByTagNameNS", &document_or_element_node::get_elements_by_tag_name_ns)
        .auto_wrap_objects();
}
