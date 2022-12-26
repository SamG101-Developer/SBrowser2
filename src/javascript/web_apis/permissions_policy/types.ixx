module;
#include "ext/macros/pimpl.hpp"
#include <tl/optional.hpp>


export module apis.webappsec_permissions_policy.types;
import apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(webappsec_permissions_policy)
{
    class permissions_policy;
    class permissions_policy_violation_report_body;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(webappsec_permissions_policy)
{
    /* [4.1] */ struct policy_controlled_feature_t;
    /* [4.2] */ struct permissions_policy_t;

    /* [4.9] */ enum class default_allowlist_t {ALL, SELF};
    enum class inherited_policy_value_t : bool {DISABLED = false, ENABLED = true};

    using feature_name_t = ext::string;
    /* [4.8] */ using allowlist_t = ext::set<html::detail::origin_t>;
    /* [4.3] */ using inherited_policy_t = ext::map<policy_controlled_feature_t, inherited_policy_value_t>;
    /* [4.4] */ using declared_policy_t = ext::map<policy_controlled_feature_t , allowlist_t>;
    /* [4.7] */ using policy_directive_t = ext::map<policy_controlled_feature_t, allowlist_t>;
    /* [4.5] */ using header_policy_t = ext::vector<policy_directive_t>;
    /* [4.6] */ using container_policy = ext::optional<policy_directive_t>;

    using header_policy_t = ext::vector<policy_directive_t>;
    using container_policy_t = policy_directive_t;

    ext::set<feature_name_t> supported_features {};
}


struct webappsec_permissions_policy::detail::policy_controlled_feature_t
{
    default_allowlist_t default_allowlist;
};


struct webappsec_permissions_policy::detail::permissions_policy_t
{
    inherited_policy_t inherited_policy;
    declared_policy_t declared_policy;

    auto empty() -> ext::boolean;
};
