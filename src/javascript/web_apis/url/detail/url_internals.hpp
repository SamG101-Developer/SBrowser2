#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_URL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_URL_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/expected.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(file_api)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)
namespace encoding {class encoding;}


namespace url::detail
{
    auto is_url_special(
            const url_t& url)
            -> ext::boolean;

    auto url_includes_credentials(
            const url_t& url)
            -> ext::boolean;

    auto url_has_opaque_path(
            const url_t& url)
            -> ext::boolean;

    auto url_cannot_have_username_password_port(
            const url_t& url)
            -> ext::boolean;

    auto is_windows_drive_letter(
            ext::string&& string)
            -> ext::boolean;

    auto is_normalized_windows_drive_letter(
            ext::string&& string)
            -> ext::boolean;

    auto starts_with_windows_drive_letter(
            ext::string&& string)
            -> ext::boolean;

    auto shorten_url_path(
            url_t& url)
            -> void;

    auto is_valid_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_absolute_url_with_fragment(
            ext::string_view string)
            -> ext::boolean;

    auto is_absolute_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_url_scheme_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_relative_url_with_fragment(
            ext::string_view string)
            -> ext::boolean;

    auto is_relative_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_scheme_relative_special_url_string(
            ext::string_view string)
            -> ext::string;

    auto is_url_port_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_scheme_relative_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_opaque_host_and_port_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_scheme_relative_file_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_path_absolute_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_path_absolute_non_windows_file_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_path_relative_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_path_relative_scheme_less_url_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_url_path_segment_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_single_dot_segment(
            ext::string_view string)
            -> ext::boolean;

    auto is_double_dot_segment(
            ext::string_view string)
            -> ext::boolean;

    auto is_url_query_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_url_fragment_string(
            ext::string_view string)
            -> ext::boolean;

    auto is_url_code_point(
            wchar_t code_point)
            -> ext::boolean;

    auto is_url_unit(
            wchar_t code_point)
            -> ext::boolean;

    auto url_parser(
            ext::string_view input,
            ext::string_view base_url = u8"",
            encoding::encoding* encoding = nullptr) // encoding::encoding::utf8)
            -> ext::expected<url_t>;

    auto basic_url_parser(
            ext::string_view input,
            ext::string_view base_url = u8"",
            encoding::encoding* encoding = nullptr, //encoding::encoding::utf8,
            ext::optional<const url_t&> url = ext::nullopt,
            state_override_t state_override = state_override_t::SCHEME_START_STATE)
            -> ext::expected<url_t>;

    auto set_username(
            url_t& url,
            ext::string&& username)
            -> void;

    auto set_password(
            url_t& url,
            ext::string&& username)
            -> void;

    auto url_serializer(
            const url_t& url,
            ext::boolean exclude_fragment  = false)
            -> ext::string;

    auto url_path_serializer(
            const url_t& url)
            -> ext::string;

    auto urls_are_equal(
            const url_t& url_a,
            const url_t& url_b,
            ext::boolean exclude_fragments)
            -> ext::boolean;

    auto origin(
            const url_t& url)
            -> html::detail::origin_t;
};


struct url::detail::url_t
{
    url_t(ext::string&& url_string);

    ext::string scheme;
    ext::string username;
    ext::string password;
    domain_t host;

    ext::number<short> port;
    ext::vector<ext::string> path;
    ext::string query;
    ext::string fragment;

    std::unique_ptr<file_api::detail::blob_url_entry_t> blob_url_entry {nullptr};
    std::unique_ptr<dom_object> object {nullptr};
};


auto operator""_url(const char* string, size_t length) {return url::detail::url_t{ext::string{string, length}};}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_URL_INTERNALS_HPP
