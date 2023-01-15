#pragma once
#include "ext/memory.ixx"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_DETAIL_GENERAL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_DETAIL_GENERAL_INTERNALS_HPP


#include "ext/optional.ixx"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include <range/v3/to_container.hpp>
#include <range/v3/view/iota.hpp>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)

namespace dom::other {class dom_exception;}


namespace fetch::detail
{
    using algorithm_t = ext::function<void(v8::Local<v8::Object>)>;

    const ext::vector<ext::number<ushort>> null_body_status {101, 103, 204, 205, 304};
    const ext::vector<ext::number<ushort>> ok_status = ranges::views::closed_iota(200, 299) | ranges::to<ext::vector<ext::number<ushort>>>;
    const ext::vector<ext::number<ushort>> redirect_status {101, 103, 204, 205, 304};


    auto report_timing(
            fetch_controller_t& controller,
            v8::Local<v8::Object> global_object)
            -> void;

    auto process_next_manual_redirect(
            fetch_controller_t& controller)
            -> void;

    auto extract_full_timing_info(
            fetch_controller_t& controller)
            -> fetch_timing_info_t*;

    auto abort_fetch_controller(
            fetch_controller_t& controller,
            ext::optional<dom::other::dom_exception> error = ext::nullopt)
            -> void;

    auto deserialize_serialized_abort_reason(
            v8::Local<v8::Object> abort_reason,
            v8::Local<v8::Context> realm)
            -> dom::other::dom_exception;

    auto terminate_fetch_controller(
            fetch_controller_t& controller)
            -> void;

    auto is_aborted(
            fetch_params_t& params)
            -> ext::boolean;

    auto is_cancelled(
            fetch_params_t& params)
            -> ext::boolean;

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
            fetch_group_t& fetch_group_object)
            -> void;

    auto create_opaque_timing_info(
            fetch_timing_info_t& timing_info)
            -> std::unique_ptr<fetch_timing_info_t>;

    template <ext::callable F>
    auto queue_fetch_task(F&& steps, html::detail::task_queue_t& task_destination) -> void;

    template <ext::callable F>
    auto queue_fetch_task(F&& steps, v8::Local<v8::Object> task_destination) -> void;
}




struct fetch::detail::fetch_timing_info_t
{
    hr_time::dom_high_res_time_stamp start_time = 0;
    hr_time::dom_high_res_time_stamp redirect_start_time = 0;
    hr_time::dom_high_res_time_stamp redirect_end_time = 0;
    hr_time::dom_high_res_time_stamp post_redirect_start_time = 0;
    hr_time::dom_high_res_time_stamp final_service_worker_start_time = 0;
    hr_time::dom_high_res_time_stamp final_network_request_start_time = 0;
    hr_time::dom_high_res_time_stamp final_network_response_start_time = 0;
    hr_time::dom_high_res_time_stamp end_time = 0;

    std::unique_ptr<connection_timing_info_t> final_connection_timing_info = nullptr;
    ext::vector<ext::string> server_timing_headers{};
    ext::boolean render_blocking = false;
};





struct fetch::detail::fetch_record_t
{
    // Don't retain any ownership over these pointers TODO ???
    std::observer_ptr<request_t> request;
    std::observer_ptr<fetch_controller_t> controller;
};


struct fetch::detail::fetch_group_t
{
    ext::vector<std::unique_ptr<fetch_record_t>> fetch_records;
    std::observer_ptr<request_t> request;
    std::observer_ptr<fetch_controller_t> fetch_controller;

    ~fetch_group_t();
};


struct fetch::detail::response_body_info_t
{
    ext::number<int> encoded_size = 0;
    ext::number<int> decoded_size = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_DETAIL_GENERAL_INTERNALS_HPP
