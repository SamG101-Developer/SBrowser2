#pragma once
#ifndef SBROWSER2_HTTP_INTERNALS_HPP
#define SBROWSER2_HTTP_INTERNALS_HPP


#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include <v8-forward.h>
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(high_resolution_time)
namespace url {class url_object;}

namespace fetch::detail
{
    using algorithm_t = ext::optional<ext::function<void(v8::Local<v8::Object>)>>;

    ext::vector<int> null_body_status {101, 103, 204, 205, 304};
    ext::vector<int> ok_status = ranges::views::closed_iota(200, 299) | ranges::to<ext::vector<int>>;
    ext::vector<int> redirect_status {101, 103, 204, 205, 304};

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
            fetch_controller_t* controller,
            v8::Local<v8::Object> global_object)
            -> void;

    auto extract_full_timing_info(
            fetch_controller_t* controller)
            -> fetch_timing_info_t*;

    auto abort_fetch_controller(
            fetch_controller_t* controller)
            -> void;

    auto terminate_fetch_controller(
            fetch_controller_t* controller)
            -> void;

    auto is_aborted(
            fetch_controller_t* controller)
            -> ext::boolean;

    auto is_cancelled(
            fetch_controller_t* controller)
            -> ext::boolean;

    auto is_url_local(
            url::url_object& url)
            -> ext::boolean;

    auto collect_http_quoted_string(
            ext::string& input,
            ext::string::iterator position,
            const ext::boolean& extract_value_flag = false)
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
            fetch_group_t* fetch_group_object)
            -> void;
}


struct fetch::detail::connection_timing_info_t
{
    high_resolution_time::dom_high_res_time_stamp_t domain_lookup_start_time = 0;
    high_resolution_time::dom_high_res_time_stamp_t domain_lookup_end_time = 0;
    high_resolution_time::dom_high_res_time_stamp_t connection_start_time = 0;
    high_resolution_time::dom_high_res_time_stamp_t connection_end_time = 0;
    high_resolution_time::dom_high_res_time_stamp_t secure_connection_start_time = 0;
    ext::string alpn_negotiated_protocol;
};


struct fetch::detail::fetch_controller_t
{
    fetch_controller_state_t state {fetch_controller_state_t::ONGOING};
    fetch_timing_info_t* full_timing_info = nullptr;
    algorithm_t report_timing_steps;
};

struct fetch::detail::fetch_timing_info_t
{
    high_resolution_time::dom_high_res_time_stamp_t start_time{0};
    high_resolution_time::dom_high_res_time_stamp_t redirect_start_time{0};
    high_resolution_time::dom_high_res_time_stamp_t redirect_end_time{0};
    high_resolution_time::dom_high_res_time_stamp_t post_redirect_start_time{0};
    high_resolution_time::dom_high_res_time_stamp_t final_service_worker_start_time{0};
    high_resolution_time::dom_high_res_time_stamp_t final_network_request_start_time{0};
    high_resolution_time::dom_high_res_time_stamp_t final_network_response_start_time{0};
    high_resolution_time::dom_high_res_time_stamp_t end_time{0};

    connection_timing_info_t* final_connection_timing_info = nullptr;
    ext::vector<ext::string> server_timing_headers{};
};


struct fetch::detail::fetch_params_t
{
    algorithm_t process_request_body_chunk_length;
    algorithm_t process_request_end_of_body;
    algorithm_t process_early_hints_response;
    algorithm_t process_response;
    algorithm_t process_response_end_of_body;
    algorithm_t process_response_consume_body;

    v8::Local<v8::Object> task_destination;
    ext::boolean cross_origin_isolated_capability = false;

    fetch_controller_t controller;
    fetch_timing_info_t timing_info;
    response_t& preloaded_response_candidate;
    request_t& request;
};


struct fetch::detail::fetch_record_t
{
    request_t& request;
    fetch_controller_t& controller;
};


struct fetch::detail::fetch_group_t
{
    ext::vector<fetch_record_t*> fetch_records;
};


struct fetch::detail::response_body_info_t
{
    ext::number<int> encoded_size{0};
    ext::number<int> decoded_size{0};
};


#endif //SBROWSER2_HTTP_INTERNALS_HPP
