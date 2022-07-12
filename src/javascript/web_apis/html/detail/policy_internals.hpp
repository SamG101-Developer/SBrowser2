#pragma once
#ifndef SBROWSER2_POLICY_INTERNALS_HPP
#define SBROWSER2_POLICY_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace content_security_policy::detail::csp_internals {struct content_security_policy;}
namespace referrer_policy {enum referrer_policy;}
namespace url {class url_object;}


namespace html::detail::policy_internals
{
    enum class embedder_policy_value_t {UNSAFE_NONE, REQUIRE_CORP, CREDENTIALLESS};
    enum class cross_origin_opener_policy_value_t{UNSAFE_NONE, SAME_ORIGIN_ALLOW_POPUPS, SAME_ORIGIN, SAME_ORIGIN_PLUS_COEP};

    struct policy_container;
    struct embedder_policy;
    struct cross_origin_opener_policy;

    auto clone_policy_container(policy_container* container) -> policy_container*;
    auto requires_storing_policy_container_in_history(url::url_object& url);
}


struct html::detail::policy_internals::policy_container
{
    ext::vector<content_security_policy::detail::csp_internals::content_security_policy> csp_list;
    std::unique_ptr<embedder_policy> embedder_policy;
    referrer_policy::referrer_policy referrer_policy;
};


struct html::detail::policy_internals::embedder_policy
{
    embedder_policy_value_t value = embedder_policy_value_t::UNSAFE_NONE;
    embedder_policy_value_t report_only_value = embedder_policy_value_t::UNSAFE_NONE;
    ext::string reporting_endpoint = "";
    ext::string report_only_reporting_endpoint = "";
};


struct html::detail::policy_internals::cross_origin_opener_policy
{
    cross_origin_opener_policy_value_t value = cross_origin_opener_policy_value_t::UNSAFE_NONE;
    cross_origin_opener_policy_value_t report_only_value = cross_origin_opener_policy_value_t::UNSAFE_NONE;
    ext::string reporting_endpoint = "";
    ext::string report_only_reporting_endpoint = "";
};


#endif //SBROWSER2_POLICY_INTERNALS_HPP
