module;
#include "ext/macros/pimpl.hpp"


export module apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(webappsec_permissions_policy)
{
    auto allowlist_matches(const allowlist_t& allowlist, const html::detail::origin_t& origin) -> ext::boolean;
    auto policy_allows_feature(const permissions_policy_t& policy, feature_name_t&& feature) -> ext::boolean; // TODO : 2nd param to `policy_controlled_feature_t`
}
