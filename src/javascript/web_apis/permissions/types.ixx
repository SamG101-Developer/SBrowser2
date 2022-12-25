module;
#include "ext/macros/pimpl.hpp"
#include <function2/function2.hpp>
#include <v8-forward.h>


export module apis.permissions.types;
import ext.core;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE(permissions)
{
    class permission_status;
    class permissions;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(permissions)
{
    struct powerful_feature_t;

    enum class permission_state_t {DENIED, GRANTED, PROMPT};

    using permission_key_t = ext::string;
    using permissions_descriptor_t = ext::map<ext::string, ext::any>;
    using permission_store_entry_t = ext::tuple<permission_descriptor_t, permission_key_t, permission_state_t>;
}


struct permissions::detail::powerful_feature_t
{
    powerful_feature_t(ext::string&& powerful_feature_name);

    ext::string name;
    ext::vector<permission_descriptor_t> aspects;

    ext::number<long double> permission_life;
    permission_state_t default_permission_state;

    // permission state constraints
    // extra permissions data constraints
    // extra permissions query algorithm

    ext::function<auto(permissions_descriptor_t&& permission_descriptor, permission_status* status) -> void> permission_query_algorithm;
    ext::function<auto(js::env::env& environment) -> permission_key_t> permission_key_generation_algorithm;
    ext::function<auto(const permission_key_t& key_a, const permission_key_t& key_b) -> bool> permission_key_comparison_algorithm;
    ext::function<auto() -> void> permission_revocation_algorithm;
};
