#pragma once
#ifndef SBROWSER2_POLICY_INTERNALS_HPP
#define SBROWSER2_POLICY_INTERNALS_HPP


#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(webappsec_csp)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
#include INCLUDE_INNER_TYPES(url)


namespace html::detail
{
    auto clone_policy_container(
            policy_container_t* container)
            -> policy_container_t*;

    auto requires_storing_policy_container_in_history(
            url::detail::url_t& url)
            -> ext::boolean;

    auto match_cross_origin_policy_opener_values(
            const cross_origin_opener_policy_value_t& policy_a,
            const origin_t& origin_a,
            const cross_origin_opener_policy_value_t& policy_b,
            const origin_t& origin_b)
            -> ext::boolean;

    auto obtain_cross_origin_opener_policy(
            const fetch::detail::response_t&,
            v8::Isolate* reserved_environment)
            -> cross_origin_opener_policy_t;
}


struct html::detail::policy_container_t
{
    ext::vector<webappsec::detail::policy_t*> csp_list;
    std::unique_ptr<embedder_policy_t> embedder_policy;
    referrer_policy::detail::referrer_policy_t referrer_policy;
};


struct html::detail::embedder_policy_t
{
    using enum embedder_policy_value_t;

    embedder_policy_value_t value = UNSAFE_NONE;
    embedder_policy_value_t report_only_value = UNSAFE_NONE;
    ext::string reporting_endpoint = u"";
    ext::string report_only_reporting_endpoint = u"";
};


struct html::detail::cross_origin_opener_policy_t
{
    using enum cross_origin_opener_policy_value_t;

    cross_origin_opener_policy_value_t value = UNSAFE_NONE;
    cross_origin_opener_policy_value_t report_only_value = UNSAFE_NONE;
    ext::string reporting_endpoint = u"";
    ext::string report_only_reporting_endpoint = u"";
};


#endif //SBROWSER2_POLICY_INTERNALS_HPP
