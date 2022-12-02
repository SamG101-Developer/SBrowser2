#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY__TYPEDEFS_HPP

#include "ext/map.ixx"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

namespace permissions_policy::detail
{
    enum class feature_t {FULLSCREEN};
    enum class inherited_policy_value_t {DISABLED, ENABLED};
    struct internal_permissions_policy_t;
    using feature_name_t = ext::string;
    using allowlist_t = ext::set<ext::string>;
    using inherited_policy_t = ext::map<feature_t, inherited_policy_value_t>;
    using declared_policy_t = ext::map<feature_t , allowlist_t>;
    using policy_directive_t = declared_policy_t;
    using header_policy_t = ext::vector<policy_directive_t>;
    using container_policy_t = policy_directive_t;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY__TYPEDEFS_HPP
