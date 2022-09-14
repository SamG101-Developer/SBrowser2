#ifndef SBROWSER2_EXTENSION_INTERNALS_HPP
#define SBROWSER2_EXTENSION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include <v8-object.h>

#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(html)


namespace fetch::detail
{
    auto append_request_origin_header(
            request_t& request_object)
            -> void;

    auto is_cors_request(
            request_t& request_object)
            -> ext::boolean;

    auto is_cors_request_response(
            response_t& response_object)
            -> ext::boolean;

    auto is_cors_preflight_request_response(
            response_t& response_object)
            -> ext::boolean;

    auto is_cors_non_preflight_request_response(
            response_t& response_object)
            -> ext::boolean;

    auto extract_length(
            const headers_t& headers)
            -> ext::number<double>;

    auto extract_mime_type(
            const headers_t& headers)
            -> ext::string;

    auto determine_nosniff(
            const headers_t& headers)
            -> ext::boolean;

    auto should_response_to_request_be_blocked_due_to_nosniff(
            request_t& request_object,
            response_t& response_object)
            -> ext::boolean;

    auto cross_origin_resource_policy_check(
            ext::string_view origin,
            v8::Local<v8::Object> settings_object,
            ext::string_view destination,
            response_t& response_object,
            ext::boolean for_navigation = false)
            -> ext::boolean;

    auto cross_origin_resource_policy_internal_check(
            ext::string_view origin,
            html::detail::embedder_policy_value_t embedder_policy_value,
            response_t& response_object,
            ext::boolean  for_navigation)
            -> void;

    auto queue_cross_origin_embedder_corp_violation_report(
            response_t& response_object,
            v8::Local<v8::Object> settings_object,
            ext::string_view destination,
            ext::boolean  report_only)
            -> void;
}


#endif //SBROWSER2_EXTENSION_INTERNALS_HPP
