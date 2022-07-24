#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_POLICY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_POLICY_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "permissions_policy/_typedefs.hpp"
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}

namespace permissions_policy::detail::policy_internals
{
    struct internal_permissions_policy;

    auto is_empty_permissions_policy(
            const internal_permissions_policy& policy)
            -> ext::boolean;

    auto observable_policy(
            dom::nodes::node* node)
            -> internal_permissions_policy&;

    auto declared_origin(
            dom::nodes::element* element)
            -> ext::string;
}


struct permissions_policy::detail::policy_internals::internal_permissions_policy
{
    inherited_policy_t inherited_policy;
    declared_policy_t declared_policy;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_POLICY_INTERNALS_HPP
