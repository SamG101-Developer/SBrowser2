#pragma once
#ifndef SBROWSER2_DIRECTIVE_INTERNALS_HPP
#define SBROWSER2_DIRECTIVE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(content_security_policy)

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}

namespace content_security_policy::detail
{
    auto pre_request_check(
            ext::string_view directive,
            const fetch::detail::request_t& request,
            const content_security_policy_t& csp)
            -> ext::string;

    auto post_request_check(
            ext::string_view directive,
            fetch::detail::request_t& request,
            fetch::detail::response_t& response,
            const content_security_policy_t& csp)
            -> ext::string;

    auto inline_check(
            ext::string_view directive,
            dom::nodes::element* element,
            ext::string_view type,
            ext::string_view source,
            const content_security_policy_t& csp)
            -> ext::string;

    auto initialization(
            ext::string_view directive,
            dom::nodes::document* document,
            const content_security_policy_t& csp)
            -> ext::string;

    auto pre_navigation_check(
            ext::string_view directive,
            const fetch::detail::request_t& request,
            ext::string_view navigation_type,
            const content_security_policy_t& csp)
            -> ext::string;

    auto navigation_response_check(
            ext::string_view directive,
            const fetch::detail::request_t& request,
            ext::string_view navigation_type,
            const fetch::detail::response_t& response,
            const html::detail::browsing_context_t& browsing_context,
            ext::string_view type,
            const content_security_policy_t& csp)
            -> ext::string;

    auto webrtc_pre_connect_check(
            const content_security_policy_t& csp)
            -> ext::string;

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
            const content_security_policy_t& csp)
            -> ext::boolean;
}


#endif //SBROWSER2_DIRECTIVE_INTERNALS_HPP
