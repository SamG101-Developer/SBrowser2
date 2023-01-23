module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>
#include <v8-forward.h>


export module apis.fetch.detail;

import apis.dom.types;
import apis.html.types;
import apis.fetch.types;
import apis.hr_time.types;
import apis.url.types;

import js.env.realms;
import js.env.settings;

import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(fetch)
{
    // Fetch controller helpers
    auto report_timing(fetch_controller_t& controller, v8::Local<v8::Object> global_object) -> void;
    auto process_next_manual_redirect(fetch_controller_t& controller) -> void;
    auto extract_full_timing_info(fetch_controller_t& controller) -> fetch_timing_info_t*;
    auto abort_fetch_controller(fetch_controller_t& controller, ext::optional<dom::dom_exception&&> error = ext::nullopt) -> void;
    auto deserialize_serialized_abort_reason(v8::Local<v8::Object> abort_reason, v8::Local<v8::Context> realm) -> dom::dom_exception;
    auto terminate_fetch_controller(fetch_controller_t& controller) -> void;

    // Fetch timing helpers
    auto create_opaque_timing_info(fetch_timing_info_t& timing_info) -> std::unique_ptr<fetch_timing_info_t>;
    template <ext::callable F> auto queue_fetch_task(F&& steps, html::detail::task_queue_t& task_destination) -> void;

    // URL helpers
    auto is_local_scheme(ext::string_view scheme) -> ext::boolean;
    auto is_http_scheme(ext::string_view scheme) -> ext::boolean;
    auto is_fetch_scheme(ext::string_view scheme) -> ext::boolean;
    auto is_url_local(url::detail::url_t& url) -> ext::boolean;

    // HTTP helpers
    template <ext::char_like T> auto is_http_newline_byte(T character) -> ext::boolean;
    template <ext::char_like T> auto is_http_tab_or_space_byte(T character) -> ext::boolean;
    template <ext::char_like T> auto is_http_whitespace_byte(T character) -> ext::boolean;
    template <ext::string_like T> auto collect_http_quoted_string(T& input, typename T::iterator& position, ext::boolean extract_value_flag = false) -> T&;

    // Method helpers
    auto is_cors_safelisted_method(method_t method) -> ext::boolean;
    auto is_forbidden_method(method_t method) -> ext::boolean;

    // Header helpers
    template <header_value_object_t T, typename U> auto get_structured_field_value(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> U;
    template <> auto get_structured_field_value<header_value_object_t::DICT>(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> ext::map<header_value_t, header_values_t>;
    template <> auto get_structured_field_value<header_value_object_t::LIST>(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> ext::vector<header_value_t>;
    template <> auto get_structured_field_value<header_value_object_t::ITEM>(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> header_value_t;
    auto header_name_matches(ext::view_of_t<header_name_t> header_name1, ext::view_of_t<header_name_t> header_name2) -> ext::boolean;
    auto set_structured_field_value(header_t&& header, headers_t& headers) -> void;
    auto contains_header(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> ext::boolean;
    auto get_header_value(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> header_value_t;
    auto get_decode_split_name(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> header_names_t;
    auto get_decode_split_value(ext::view_of_t<header_value_t> header_value, ext::view_of_t<headers_t> headers) -> header_names_t;
    auto append_header(header_t&& header, headers_t& headers) -> void;
    auto delete_header(ext::view_of_t<header_name_t> header_name, headers_t& headers) -> void;
    auto set_header(header_t&& header, headers_t& headers) -> void;
    auto combine_header(header_t&& header, headers_t& headers) -> void;
    auto convert_header_names_to_sorted_lowercase_set(ext::view_of_t<header_names_t> header_names) -> header_names_t;
    auto sort_and_combine(ext::view_of_t<headers_t> headers) -> headers_t;
    auto is_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;
    auto is_header_value(ext::view_of_t<header_value_t> header_value) -> ext::boolean;
    auto normalize(header_value_t& potential_value) -> header_value_t&;

    template <ext::char_like T> auto is_cors_unsafe_request_header_byte(T byte) -> ext::boolean;
    auto cors_unsafe_request_header_names(ext::view_of_t<headers_t> headers) -> header_names_t;

    auto is_cors_non_wildcard_request_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;
    auto is_privileged_no_cors_request_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;
    auto is_request_body_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;
    auto is_cors_safelisted_response_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;
    auto is_no_cors_safelisted_request_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;
    auto is_forbidden_response_header_name(ext::view_of_t<header_name_t> header_name) -> ext::boolean;

    auto is_cors_safelisted_request_header(const header_t& header) -> ext::boolean;
    auto is_no_cors_safelisted_request_header(const header_t& header) -> ext::boolean;
    auto is_forbidden_request_header(const header_t& header) -> ext::boolean;

    auto extract_header_values(ext::view_of_t<header_name_t> header) -> ext::expected<header_values_t>;
    auto extract_header_list_values(ext::view_of_t<header_name_t> header_name, ext::view_of_t<headers_t> headers) -> ext::expected<header_values_t>;
    auto parse_single_range_header_value(ext::view_of_t<header_value_t> header_value) -> ext::boolean;

    auto default_user_agent_value() -> header_value_t;
    auto document_accept_header_value() -> header_value_t;

    auto extract_length(const headers_t& headers) -> ext::number<double>;
    auto extract_mime_type(const headers_t& headers) -> ext::string;
    auto determine_nosniff(const headers_t& headers) -> ext::boolean;

    auto cross_origin_resource_policy_check(ext::string_view origin, v8::Local<v8::Object> settings_object, ext::string_view destination, response_t& response_object, ext::boolean for_navigation = false) -> ext::boolean;
    auto cross_origin_resource_policy_internal_check(ext::string_view origin, html::detail::embedder_policy_value_t embedder_policy_value, response_t& response_object, ext::boolean  for_navigation) -> void;
    auto queue_cross_origin_embedder_corp_violation_report(response_t& response_object, v8::Local<v8::Object> settings_object, ext::string_view destination, ext::boolean  report_only) -> void;

    // Status helpers
    auto is_status(status_t integer) -> ext::boolean;
    auto is_null_body_status(status_t integer) -> ext::boolean;
    auto is_ok_status(status_t integer) -> ext::boolean;
    auto is_redirect_body_status(status_t integer) -> ext::boolean;

    // Body helpers
    auto clone_body(body_t& body) -> std::unique_ptr<body_t>;
    auto get_byte_sequence_as_body(ext::u8string&& byte_sequence) -> std::unique_ptr<body_t>;
    template <ext::callable T, ext::callable U, ext::callable V> auto incrementally_read_body(body_t& body, T&& process_body_chunk, U&& process_end_of_body, V&& process_body_error, task_destination_t&& task_destination) -> void;
    template <ext::callable T, ext::callable U, ext::callable V> auto incrementally_read_loop(streams::readable_stream_default_reader* reader, task_destination_t&& task_destination, T&& process_body_chunk, U&& process_end_of_body, V&& process_body_error) -> void;
    template <ext::callable T, ext::callable U> auto fully_read_body(body_t& body, T&& process_body, U&& process_body_error, task_destination_t&& task_destination) -> void;
    auto handle_content_encodings(ext::string_view codings, ext::u8string_view bytes) -> ext::expected<ext::u8string>; // TODO - check types

    auto is_unusable(mixins::body* body) -> ext::boolean;
    auto consume_body(mixins::body* body, ext::string_view type) -> ext::promise<ext::u8string>; // TODO: <T>?
    auto safely_extract_body(body_init_t&& object) -> detail::body_with_type_t;
    auto extract(body_init_t&& object, ext::boolean keepalive = false) -> detail::body_with_type_t;

    // Request helpers
    auto is_subresource_request(const request_t& request) -> ext::boolean;
    auto is_non_subresource_request(const request_t& request) -> ext::boolean;
    auto is_navigation_request(const request_t& request) -> ext::boolean;
    auto has_redirect_tainted_origin(const request_t& request) -> ext::boolean;
    auto serialize_request_origin(const request_t& request) -> ext::string;
    auto byte_serializing_request_origin(const request_t& request) -> ext::string;
    auto clone_request(const request_t& request) -> std::unique_ptr<request_t>;
    auto check_if_cross_origin_embedder_policy_allows_credentials(const request_t& request) -> ext::boolean;
    auto append_range_header_to_request(request_t& request, ext::number<int> first, ext::number<int> last = -1) -> void;
    auto append_origin_header_to_request(request_t& request_object) -> void;

    auto is_cors_request(request_t& request_object) -> ext::boolean;
    auto is_cors_preflight_request(request_t& request_object) -> ext::boolean;

    auto create_request_object(std::unique_ptr<request_t>&& inner_request, header_guard_t header_guard) -> std::unique_ptr<request>;

    // Response helpers
    auto serialize_response_url_for_reporting(const response_t& response) -> ext::string;
    auto is_aborted_network_error(const response_t& response) -> ext::boolean;
    auto is_network_error(const response_t& response) -> ext::boolean;
    auto create_appropriate_network_error(const fetch_params_t& params) -> std::unique_ptr<response_t>;

    auto is_filtered_response(const response_t& response) -> ext::boolean;
    auto is_basic_filtered_response(const response_t& response) -> ext::boolean;
    auto is_cors_filtered_response(const response_t& response) -> ext::boolean;
    auto is_opaque_filtered_response(const response_t& response) -> ext::boolean;
    auto is_opaque_redirect_filtered_response(const response_t& response) -> ext::boolean;
    auto is_fresh_response(const response_t& response) -> ext::boolean;
    auto is_stale_while_revalidate_response(const response_t& response) -> ext::boolean;
    auto is_stale_response(const response_t& response) -> ext::boolean;

    auto clone_response(const response_t& response) -> std::unique_ptr<response_t>;
    auto location_url(const response_t& response) -> ext::expected<url::detail::url_t>;

    auto should_response_to_request_be_blocked_due_to_nosniff(request_t& request_object, response_t& response_object) -> ext::boolean;

    auto create_response_object(std::unique_ptr<response_t>&& inner_response, header_guard_t header_guard) -> std::unique_ptr<response>;
    auto initialize_response_object(response* response_object, response_init_t&& init, body_with_type_t&& body = nullptr) -> void;

    // Miscellaneous helpers
    auto is_potential_destination(potential_destination_t&& destination);
    auto translate_potential_destination(potential_destination_t&& potential_destination) -> destination_t;

    // Fetch helpers
    auto terminate_fetch_group(fetch_group_t& fetch_group_object) -> void;

    template <ext::callable T, ext::callable U, ext::callable V, ext::callable W, ext::callable X, ext::callable Y>
    auto fetch(request_t& request, T&& process_request_body_chunk_length = nullptr, U&& process_request_end_of_body = nullptr, V&& process_early_hints_response = nullptr, W&& process_response = nullptr, X&& process_response_end_of_body = nullptr, Y&& process_response_consume_body = nullptr, ext::boolean use_parallel_queue = false) -> std::unique_ptr<response_t>;
    auto main_fetch(fetch_params_t& fetch_params, ext::boolean recursive = false) -> std::unique_ptr<response_t>;
    auto fetch_response_handover(fetch_params_t& fetch_params, response_t& response) -> void;
    auto scheme_fetch(fetch_params_t& fetch_params) -> std::unique_ptr<response_t>;
    auto http_fetch(fetch_params_t& fetch_params, ext::boolean make_cors_preflight = false) -> std::unique_ptr<response_t>;
    auto http_redirect_fetch(fetch_params_t& fetch_params, response_t& response) -> std::unique_ptr<response_t>;
    auto http_navigate_redirect_fetch(request_t& request, response_t& response) -> std::unique_ptr<response_t>;
    auto http_network_or_cache_fetch(fetch_params_t& fetch_params, ext::boolean is_authentication_fetch = false, ext::boolean is_new_connection_fetch = false) -> std::unique_ptr<response_t>;
    auto http_network_fetch(fetch_params_t& fetch_params, ext::boolean include_credentials = false, ext::boolean force_new_connection = false) -> std::unique_ptr<response_t>;
    auto cors_preflight_request(request_t& request) -> std::unique_ptr<response_t>;
    auto cors_check(request_t& request, response_t& response) -> ext::boolean;
    auto tao_check(request_t& request, response_t& response) -> ext::boolean;

    // Connection helpers
    auto resolve_origin(const network_partition_key_t& key, const html::detail::origin_t& origin) -> ext::expected<ext::vector<ext::string>>;
    auto clamp_and_coarsen_connection_timing_information(const connection_timing_info_t& timing_information, hr_time::dom_high_res_time_stamp default_start_time, ext::boolean cross_origin_isolated_capability) -> std::unique_ptr<connection_timing_info_t>;
    auto obtain_connection(const network_partition_key_t& key, const url::detail::url_t& url, ext::boolean credentials, new_connection_setting_t new_ = new_connection_setting_t::NO, ext::boolean http3_only = false) -> ext::expected<std::unique_ptr<connection_t>>;
    auto create_connection(const network_partition_key_t& key, const html::detail::origin_t& origin, ext::boolean credentials, ext::string_view proxy, ext::string_view host, const connection_timing_info_t& timing_info, ext::boolean http3_only = false) -> ext::expected<std::unique_ptr<connection_t>>;
    auto record_timing_information(const connection_t& connection) -> void;
    auto determine_network_partition_key(js::env::settings_t* environment_settings) -> network_partition_key_t;
    auto determine_network_partition_key(const request_t& request) -> network_partition_key_t;
    auto determine_http_cache_partition(const request_t& request) -> ext::string;
    auto should_block_due_to_bad_port(const request_t& request) -> ext::boolean;
    auto should_block_due_to_mime_type(const request_t& request) -> ext::boolean;

    // Cache helpers
    auto create_a_new_cache_entry(request_t& request, ext::number<int> max_age, ext::string_view method, header_name_t header_name) -> std::unique_ptr<cache_entry_t>;
    auto clear_cache_entries(request_t& request) -> void;
    auto cache_entry_match(const cache_entry_t&, const request_t&) -> ext::boolean;
    auto method_cache_entry_match(method_t, const request_t&) -> ext::boolean;
    auto header_name_cache_entry_match(ext::view_of_t<header_name_t>, const request_t&) -> ext::boolean;
}
