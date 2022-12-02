#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_POLICY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_POLICY_INTERNALS_HPP

#include "ext/boolean.ixx"
#include INCLUDE_INNER_TYPES(permissions_policy)
namespace dom::nodes {class node;}
namespace html::elements {class html_iframe_element;}

namespace permissions_policy::detail
{
    auto is_empty_permissions_policy(
            const internal_permissions_policy_t& policy)
            -> ext::boolean;

    auto observable_policy(
            dom::nodes::node* node)
            -> internal_permissions_policy_t;

    auto declared_origin(
            html::elements::html_iframe_element* element)
            -> ext::string;
}


struct permissions_policy::detail::internal_permissions_policy_t
{
    inherited_policy_t inherited_policy;
    declared_policy_t declared_policy;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_POLICY_INTERNALS_HPP
