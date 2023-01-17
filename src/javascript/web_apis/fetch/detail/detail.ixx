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
}
