module;
#include "ext/macros/pimpl.hpp"
#include <swl/variant.hpp>
#include <tl/optional.hpp>
#include <v8-forward.h>


export module apis.permissions.detail;
import apis.permissions.types;
import ext.core;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(permissions)
{
    /* [5.1.1] */ auto get_current_permission_state(ext::string&& name, const js::env::env& environment) -> permission_state_t;
    /* [5.1.2] */ auto permission_state(permission_descriptor_t&& permission_descriptor, const js::env::env& environment = js::env::env::current()) -> permission_state_t;
    /* [5.2.1] */ auto request_permission_to_use(permission_descriptor_t&& permission_descriptor) -> permission_state_t;
    /* [5.3.1] */ auto prompt_user_to_choose(permission_descriptor_t&& permission_descriptor, ext::boolean allow_multiple = false) -> ext::variant<permission_state_t, ext::vector<permissions_policy::detail::feature_t>>;
    /* [5.4.1] */ auto react_to_user_revoking_permission() -> void;
};
