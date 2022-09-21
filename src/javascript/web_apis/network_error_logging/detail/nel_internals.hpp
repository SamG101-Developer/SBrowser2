#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NETWORK_ERROR_LOGGING_DETAIL_NEL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NETWORK_ERROR_LOGGING_DETAIL_NEL_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(network_error_logging)
#include INCLUDE_INNER_TYPES(referrer_policy)


namespace network_error_logging::detail
{
    auto successful_request(
            const fetch::detail::request_t& request)
            -> ext::boolean;

    auto failed_request(
            const fetch::detail::request_t& request)
            -> ext::boolean;

    auto process_policy_headers(
            const fetch::detail::request_t& request,
            const fetch::detail::response_t& response)
            -> void;

    auto choose_policy_for_origin(
            ext::string&& origin)
            -> ext::optional<nel_policy_t>;

    auto extract_request_headers(
            const fetch::detail::request_t& request,
            const nel_policy_t& policy)
            -> fetch::detail::headers_t;

    auto extract_response_headers(
            const fetch::detail::response_t& response,
            const nel_policy_t& policy)
            -> fetch::detail::headers_t;

    auto generate_network_error_report(
            const fetch::detail::request_t& request,
            const fetch::detail::response_t& response)
            -> ext::tuple<report_body_t, nel_policy_t>;

    auto deliver_network_report(
            const report_body_t& report)
            -> void;
};


struct network_error_logging::detail::report_body_t
{
    referrer_policy::detail::referrer_policy_t referrer; // TODO : type?
    ext::number<double> sampling_fraction;
    ext::string server_ip;
    ext::string protocol;
    fetch::detail::method_t method;
    fetch::detail::headers_t request_headers;
    fetch::detail::headers_t response_headers;
    ext::number<int> status_code;
    ext::number<size_t> elapsed_time;

    auto phase() -> ext::variant<network_error_phase_t, network_request_phase_t>;
    auto type() -> ext::string;
};


struct network_error_logging::detail::network_error_report_t
{
    network_error_type_t type;
    network_error_phase_t phase;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NETWORK_ERROR_LOGGING_DETAIL_NEL_INTERNALS_HPP
