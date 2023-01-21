module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>
#include <v8-forward.h>


export module apis.fetch.detail;

import apis.dom.types;
import apis.fetch.types;
import apis.url.types;
import ext.core;


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

    auto is_cors_safelisted_request_header(header_t&& header) -> ext::boolean;
}
