#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_URL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_URL_INTERNALS_HPP


#include "ext/expected.ixx"

#include "ext/optional.ixx"

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(file_api)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)
namespace encoding {class encoding;}
namespace url {class url_search_params;}
class dom_object;


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
            ext::string_view base_url = u"",
            encoding::encoding* encoding = nullptr) // encoding::encoding::utf8)
            -> ext::expected<std::unique_ptr<url_t>>;

    auto basic_url_parser(
            ext::string_view input,
            ext::string_view base_url = u"",
            encoding::encoding* encoding = nullptr, //encoding::encoding::utf8,
            ext::optional<const url_t&> url = ext::nullopt,
            state_override_t state_override = state_override_t::SCHEME_START_STATE)
            -> ext::expected<std::unique_ptr<url_t>>;

    auto set_username(
            url_t& url,
            ext::string&& username)
            -> ext::string;

    auto set_password(
            url_t& url,
            ext::string&& username)
            -> ext::string;

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
            -> std::unique_ptr<html::detail::origin_t>;

    auto update_url_search_params(
            url_search_params* query)
            -> void;
};


struct url::detail::url_t
{
    url_t(ext::string&& url_string);
    url_t(const url_t&);

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

    auto operator*() -> ext::string {return url_serializer(*this);}
};


auto operator""_url(const char16_t* string, size_t length) -> std::unique_ptr<url::detail::url_t>; // TODO{return url::detail::url_t{ext::string{string, length}};}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_URL_INTERNALS_HPP
