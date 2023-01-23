module;
#include "ext/macros.hpp"


export module apis.referrer_policy.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(referrer_policy)
{
    enum referrer_policy_t {
        _, NO_POLICY, NO_REFERRER, NO_REFERRER_WHEN_DOWNGRADE, SAME_ORIGIN, ORIGIN, STRUCT_ORIGIN,
        ORIGIN_WHEN_CROSS_ORIGIN, STRICT_ORIGIN_WHEN_ROSS_ORIGIN, UNSAFE_URL};
}
