#pragma once
#ifndef SBROWSER2_DIRECTIVE_INTERNALS_HPP
#define SBROWSER2_DIRECTIVE_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(webappsec)
#include INCLUDE_INNER_TYPES(webappsec_csp)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}


namespace webappsec::detail
{
    auto pre_request_check(
            const directive_t& directive,
            const fetch::detail::request_t& request,
            const policy_t& csp)
            -> should_t;

    auto post_request_check(
            const directive_t& directive,
            const fetch::detail::request_t& request,
            const fetch::detail::response_t& response,
            const policy_t& csp)
            -> should_t;

    auto inline_check(
            const directive_t& directive,
            dom::nodes::element* element,
            ext::string_view type,
            ext::string_view source,
            const policy_t& csp)
            -> should_t;

    auto initialization(
            const directive_t& directive,
            dom::nodes::document* document,
            const policy_t& csp)
            -> should_t;

    auto pre_navigation_check(
            const directive_t& directive,
            const fetch::detail::request_t& request,
            ext::string_view navigation_type,
            const policy_t& csp)
            -> should_t;

    auto navigation_response_check(
            const directive_t& directive,
            const fetch::detail::request_t& request,
            ext::string_view navigation_type,
            const fetch::detail::response_t& response,
            const html::detail::browsing_context_t& browsing_context,
            ext::string_view type,
            const policy_t& csp)
            -> should_t;

    auto webrtc_pre_connect_check(
            const policy_t& csp)
            -> should_t;

    auto effective_directive_for_request(
            const fetch::detail::request_t& request)
            -> ext::string;

    auto get_effective_directive_inline_checks(
            ext::string_view type)
            -> ext::string;
    
    auto get_fetch_directive_fallback_list(
            ext::string_view directive_name)
            -> ext::vector<ext::string>;
    
    auto should_fetch_directive_execute(
            ext::string_view effective_directive_name,
            ext::string_view directive_name,
            const policy_t& csp)
            -> ext::boolean;
}


struct webappsec::detail::directive_value_t
{
    ext::set<ext::string> source_list;
};


#endif //SBROWSER2_DIRECTIVE_INTERNALS_HPP
