#include "policy_internals.hpp"

#include "dom/nodes/document.hpp"

#include "html/detail/miscellaneous_internals.hpp"
#include "html/elements/html_iframe_element.hpp"

#include "permissions_policy/detail/algorithm_internals.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/unique.hpp>
#include <range/v3/view/map.hpp>


auto permissions_policy::detail::policy_internals::is_empty_permissions_policy(
        const internal_permissions_policy& policy)
        -> ext::boolean
{
    using enum inherited_policy_value_t;

    // a 'permissions_policy' is empty if all the policies are in the enabled state, and the declared policies are an
    // empty map
    return ranges::all_of(policy.inherited_policy, [](auto&& pair) {return pair.second == ENABLED;})
            && policy.declared_policy.empty();
}


auto permissions_policy::detail::policy_internals::observable_policy(
        dom::nodes::node* node)
        -> internal_permissions_policy // NOTE: intentional copy
{
    if (auto* document_node = dynamic_cast<dom::nodes::document*>(node))
        return *document_node->m_permissions_policy;

    else if (auto* element_node = dynamic_cast<html::elements::html_iframe_element*>(node))
        return detail::algorithm_internals::create_permissions_policy_for_feature_in_container_at_origin(element_node, declared_origin(element_node));

    return internal_permissions_policy{};
}


auto permissions_policy::detail::policy_internals::declared_origin(
        html::elements::html_iframe_element* element)
        -> ext::string
{
    // TODO : sandboxing

    auto element_src_url_object = html::detail::miscellaneous_internals::parse_url(element->src(), element->owner_document());

    return_if(!element->sandbox().empty() && ranges::contains(element->sandbox(), "allow-same-origin")) {}; // TODO : unique opaque origin
    return_if(!element->srcdoc().empty()) element->owner_document()->m_origin;
    return_if(!element->src().empty() && element_src_url_object.second) element_src_url_object.second.origin();

    return element->owner_document()->m_origin;
}
