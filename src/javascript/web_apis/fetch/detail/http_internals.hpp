#pragma once
#ifndef SBROWSER2_HTTP_INTERNALS_HPP
#define SBROWSER2_HTTP_INTERNALS_HPP


#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include "request_internals.hpp"

#include "high_resolution_time/_typedefs.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/view/iota.hpp>
#include <v8-local-handle.h>
#include <v8-object.h>
namespace url {class url_object;}

namespace fetch::detail::http_internals
{
    using algorithm_t = ext::optional<ext::function<void(v8::Local<v8::Object>)>>;
    
    enum class fetch_controller_state_t {ONGOING, TERMINATED, ABORTED};
    enum class method_t {DELETE, GET, HEAD, OPTIONS, POST, PUT};

    ext::vector<int> null_body_status {101, 103, 204, 205, 304};
    ext::vector<int> ok_status = ranges::views::closed_iota(200, 299) | ranges::to<ext::vector<int>>;
    ext::vector<int> redirect_status {101, 103, 204, 205, 304};

    struct connection_timing_info;
    struct fetch_controller;
    struct fetch_timing_info;
    struct fetch_params;
    struct fetch_record;
    struct fetch_group;
    struct response_body_info;

    auto is_http_tab_or_space_byte(
            char32_t charater)
            -> ext::boolean;

    auto is_http_whitespace_byte(
            char32_t charater)
            -> ext::boolean;

    auto is_http_newline_byte(
            char32_t charater)
            -> ext::boolean;

    auto report_timing(
            fetch_controller* controller,
            v8::Local<v8::Object> global_object)
            -> void;

    auto extract_full_timing_info(
            fetch_controller* controller)
            -> fetch_timing_info*;

    auto abort_fetch_controller(
            fetch_controller* controller)
            -> void;

    auto terminate_fetch_controller(
            fetch_controller* controller)
            -> void;

    auto is_aborted(
            fetch_controller* controller)
            -> ext::boolean;

    auto is_cancelled(
            fetch_controller* controller)
            -> ext::boolean;

    auto is_url_local(
            url::url_object& url)
            -> ext::boolean;

    auto collect_http_quoted_string(
            ext::string& input,
            ext::string::iterator position,
            ext::boolean_view extract_value_flag = false)
            -> ext::string;

    auto is_cors_safelisted_method(
            ext::string_view method)
            -> ext::boolean;

    auto is_forbidden_method(
            ext::string_view method)
            -> ext::boolean;

    auto normalize_method(
            ext::string_view method)
            -> ext::string;

    auto translate_potential_destination(
            ext::string_view potential_destination)
            -> ext::string;

    auto terminate_fetch_group(
            fetch_group* fetch_group_object)
            -> void;
}


struct fetch::detail::http_internals::connection_timing_info
{
    high_resolution_time::dom_high_res_time_stamp domain_lookup_start_time = 0;
    high_resolution_time::dom_high_res_time_stamp domain_lookup_end_time = 0;
    high_resolution_time::dom_high_res_time_stamp connection_start_time = 0;
    high_resolution_time::dom_high_res_time_stamp connection_end_time = 0;
    high_resolution_time::dom_high_res_time_stamp secure_connection_start_time = 0;
    ext::string alpn_negotiated_protocol;
};


struct fetch::detail::http_internals::fetch_controller
{
    fetch_controller_state_t state {fetch_controller_state_t::ONGOING};
    fetch_timing_info* full_timing_info = nullptr;
    algorithm_t report_timing_steps;
};

struct fetch::detail::http_internals::fetch_timing_info
{
    high_resolution_time::dom_high_res_time_stamp start_time{0};
    high_resolution_time::dom_high_res_time_stamp redirect_start_time{0};
    high_resolution_time::dom_high_res_time_stamp redirect_end_time{0};
    high_resolution_time::dom_high_res_time_stamp post_redirect_start_time{0};
    high_resolution_time::dom_high_res_time_stamp final_service_worker_start_time{0};
    high_resolution_time::dom_high_res_time_stamp final_network_request_start_time{0};
    high_resolution_time::dom_high_res_time_stamp final_network_response_start_time{0};
    high_resolution_time::dom_high_res_time_stamp end_time{0};

    connection_timing_info* final_connection_timing_info = nullptr;
    ext::string_vector server_timing_headers{};
};


struct fetch::detail::http_internals::fetch_params
{
    algorithm_t process_request_body_chunk_length;
    algorithm_t process_request_end_of_body;
    algorithm_t process_early_hints_response;
    algorithm_t process_response;
    algorithm_t process_response_end_of_body;
    algorithm_t process_response_consume_body;

    v8::Local<v8::Object> task_destination;
    ext::boolean cross_origin_isolated_capability = false;

    fetch_controller controller;
    fetch_timing_info timing_info;
    response& preloaded_response_candidate;
    request_internals::internal_request& request;
};


struct fetch::detail::http_internals::fetch_record
{
    request_internals::internal_request& request;
    fetch_controller& controller;
};


struct fetch::detail::http_internals::fetch_group
{
    ext::vector<fetch_record*> fetch_records;
};


struct fetch::detail::http_internals::response_body_info
{
    ext::number<int> encoded_size{0};
    ext::number<int> decoded_size{0};
};


#endif //SBROWSER2_HTTP_INTERNALS_HPP
