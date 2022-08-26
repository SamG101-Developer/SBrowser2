#pragma once
#ifndef SBROWSER2_POLICY_INTERNALS_HPP
#define SBROWSER2_POLICY_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(content_security_policy)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(referrer_policy)
#include USE_INNER_TYPES(url)


namespace html::detail
{
    auto clone_policy_container(policy_container_t* container) -> policy_container_t*;
    auto requires_storing_policy_container_in_history(url::detail::url_t& url);
}


struct html::detail::policy_container_t
{
    ext::vector<content_security_policy::detail::content_security_policy_t*>& csp_list;
    std::unique_ptr<embedder_policy_t> embedder_policy;
    referrer_policy::detail::referrer_policy_t referrer_policy;
};


struct html::detail::embedder_policy_t
{
    using enum embedder_policy_value_t;

    embedder_policy_value_t value = UNSAFE_NONE;
    embedder_policy_value_t report_only_value = UNSAFE_NONE;
    ext::string reporting_endpoint = "";
    ext::string report_only_reporting_endpoint = "";
};


struct html::detail::cross_origin_opener_policy_t
{
    using enum cross_origin_opener_policy_value_t;

    cross_origin_opener_policy_value_t value = UNSAFE_NONE;
    cross_origin_opener_policy_value_t report_only_value = UNSAFE_NONE;
    ext::string reporting_endpoint = "";
    ext::string report_only_reporting_endpoint = "";
};


#endif //SBROWSER2_POLICY_INTERNALS_HPP
