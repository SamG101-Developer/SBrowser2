#ifndef SBROWSER2_REFERRER_POLICY_HPP
#define SBROWSER2_REFERRER_POLICY_HPP

namespace referrer_policy {enum referrer_policy;}


enum referrer_policy::referrer_policy
{
    NO_POLICY,
    NO_REFERRER,
    NO_REFERRER_WHEN_DOWNGRADE,
    SAME_ORIGIN,
    ORIGIN,
    STRUCT_ORIGIN,
    ORIGIN_WHEN_CROSS_ORIGIN,
    STRICT_ORIGIN_WHEN_ROSS_ORIGIN,
    UNSAFE_URL
};


#endif //SBROWSER2_REFERRER_POLICY_HPP
