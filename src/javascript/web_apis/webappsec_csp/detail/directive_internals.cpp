#include "directive_internals.hpp"


auto webappsec::detail::pre_request_check(
        const webappsec::detail::directive_t& directive,
        const fetch::detail::request_t& request,
        const webappsec::detail::policy_t& csp)
        -> should_t
{
    return should_t::ALLOWED;
}


auto webappsec::detail::post_request_check(
        const webappsec::detail::directive_t& directive,
        const fetch::detail::request_t& request,
        const fetch::detail::response_t& response,
        const webappsec::detail::policy_t& csp)
        -> should_t
{
    return should_t::ALLOWED;
}


auto webappsec::detail::inline_check(
        const webappsec::detail::directive_t& directive,
        dom::nodes::element* element,
        ext::string_view type,
        ext::string_view source,
        const webappsec::detail::policy_t& csp)
        -> should_t
{
    return should_t::ALLOWED;
}


auto webappsec::detail::initialization(
        const webappsec::detail::directive_t& directive,
        dom::nodes::document* document,
        const webappsec::detail::policy_t& csp)
        -> should_t
{
    return should_t::ALLOWED;
}


auto webappsec::detail::pre_navigation_check(
        const webappsec::detail::directive_t& directive,
        const fetch::detail::request_t& request,
        ext::string_view navigation_type,
        const webappsec::detail::policy_t& csp)
        -> should_t
{
    return should_t::ALLOWED;
}


auto webappsec::detail::navigation_response_check(
        const webappsec::detail::directive_t& directive,
        const fetch::detail::request_t& request,
        ext::string_view navigation_type,
        const fetch::detail::response_t& response,
        const html::detail::browsing_context_t& browsing_context,
        ext::string_view type,
        const webappsec::detail::policy_t& csp) -> should_t
{
    return should_t::ALLOWED;
}


auto webappsec::detail::webrtc_pre_connect_check(
        const webappsec::detail::policy_t& csp)
        -> should_t
{
    return should_t::ALLOWED;
}
