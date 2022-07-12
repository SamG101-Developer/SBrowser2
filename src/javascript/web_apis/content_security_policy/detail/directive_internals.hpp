#pragma once
#ifndef SBROWSER2_DIRECTIVE_INTERNALS_HPP
#define SBROWSER2_DIRECTIVE_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace content_security_policy::detail::csp_internals {class content_security_policy;}
namespace fetch::detail::request_internals {struct internal_request;}
namespace fetch::detail::response_internals {struct internal_response;}
namespace html::detail::context_internals {struct browsing_context;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}

namespace content_security_policy::detail::directive_internals
{
    auto pre_request_check(
            ext::string_view directive,
            fetch::detail::request_internals::internal_request& request,
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto post_request_check(
            ext::string_view directive,
            fetch::detail::request_internals::internal_request& request,
            fetch::detail::response_internals::internal_response& response,
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto inline_check(
            ext::string_view directive,
            dom::nodes::element* element,
            ext::string_view type,
            ext::string_view source,
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto initialization(
            ext::string_view directive,
            dom::nodes::document* document,
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto pre_navigation_check(
            ext::string_view directive,
            fetch::detail::request_internals::internal_request& request,
            ext::string_view navigation_type,
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto navigation_response_check(
            ext::string_view directive,
            fetch::detail::request_internals::internal_request& request,
            ext::string_view navigation_type,
            fetch::detail::response_internals::internal_response& response,
            html::detail::context_internals::browsing_context* browsing_context,
            ext::string_view type,
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto webrtc_pre_connect_check(
            csp_internals::content_security_policy& csp)
            -> ext::string;

    auto effective_directive_for_request(
            fetch::detail::request_internals::internal_request& request)
            -> ext::string;

    auto get_effective_directive_inline_checks(
            ext::string_view type)
            -> ext::string;
    
    auto get_fetch_directive_fallback_list(
            ext::string_view directive_name)
            -> ext::string_vector;
    
    auto should_fetch_directive_execute(
            ext::string_view effective_directive_name,
            ext::string_view directive_name,
            csp_internals::content_security_policy& csp)
            -> ext::boolean;
}


#endif //SBROWSER2_DIRECTIVE_INTERNALS_HPP
