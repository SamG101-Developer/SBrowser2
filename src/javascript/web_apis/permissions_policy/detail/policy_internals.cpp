#include "policy_internals.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"

#include <range/v3/algorithm/all_of.hpp>
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
        -> internal_permissions_policy&
{
    if (auto* document_node = dynamic_cast<dom::nodes::document*>(node))
        return *document_node->m_permissions_policy;

    else if (auto* element_node = dynamic_cast<dom::nodes::element*>(node))
    {

    }
}
