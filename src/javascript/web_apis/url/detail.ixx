module;
#include <function2/function2.hpp>
#include <tl/optional.hpp>


export module apis.url.detail;

import apis.url.types;
import ext.core;


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

    auto is_host_opaque(
            domain_t&& host)
            -> ext::boolean;

    auto is_empty_host(
            domain_t&& host)
            -> ext::boolean;

    auto is_forbidden_host_code_point(
            wchar_t code_point)
            -> ext::boolean;

    auto host_public_suffix(
            domain_t&& host)
            -> ext::string;

    auto host_registerable_domain(
            domain_t&& host)
            -> ext::string;

    auto domain_to_ascii(
            domain_t&& domain,
            ext::boolean be_strict)
            -> ext::optional<ext::string>;

    auto domain_to_unicode(
            domain_t&& domain)
            -> ext::optional<ext::string>;

    auto is_valid_host_string(
            domain_t&& host)
            -> ext::boolean;

    auto is_valid_domain_string(
            domain_t&& domain)
            -> ext::boolean;

    auto is_valid_ipv4_address_string(
            domain_t&& domain)
            -> ext::boolean;

    auto is_valid_ipv6_address_string(
            domain_t&& domain)
            -> ext::boolean;

    auto is_valid_opaque_host_string(
            domain_t&& domain)
            -> ext::boolean;

    auto host_parser(
            domain_t&& input,
            ext::boolean is_not_special = false)
            -> ext::optional<domain_t>;

    auto ipv4_parser(
            domain_t&& input)
            -> ext::optional<ext::number<char>>;

    auto ipv6_parser(
            domain_t&& input)
            -> ext::optional<ext::number<char>>;

    auto ipv4_number_parser(
            domain_t&& input)
            -> ext::optional<ext::number<char>>;

    auto opaque_host_parser(
            domain_t&& input)
            -> ext::optional<domain_t>;

    auto ends_in_number_checker(
            ext::string&& input)
            -> ext::boolean;

    auto host_serializer(
            ext::string_view host)
            -> domain_t;

    auto ipv4_serializer(
            ext::string_view address)
            -> domain_t;

    auto ipv6_serializer(
            ext::string_view address)
            -> domain_t;

    auto is_percent_encoded_byte(
            char8_t)
            -> ext::boolean;

    auto percent_encode(
            std::byte byte)
            -> ext::string;

    auto percent_decode(
            ext::string byte_sequence)
            -> ext::string;

    auto percent_encode_after_encoding(
            encoding::encoding* encoding,
            ext::string&& input,
            ext::function<ext::boolean(char8_t)>&& percent_encodable_set)
            -> ext::string;

    auto utf8_percent_encode(
            char16_t code_point,
            encoding::encoding* percent_encode_set)
            -> char16_t;

    auto utf8_percent_decode(
            char16_t code_point,
            encoding::encoding* percent_encode_set)
            -> char16_t;

    auto is_c0_control_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_fragment_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_query_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_special_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_path_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_userinfo_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_component_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto is_application_x_www_form_url_encoded_percent_encodable(
            char16_t code_point)
            -> ext::boolean;

    auto application_x_www_form_urlencoded_parser(
            ext::string_view input)
            -> ext::map<ext::string, ext::string>;

    auto application_x_www_form_urlencoded_serializer(
            ext::map_span<ext::string, ext::string> tuples,
            encoding::encoding* encoding = nullptr)
            -> ext::string;

    auto application_x_www_form_urlencoded_string_parser(
            ext::string_view input)
            -> ext::map<ext::string, ext::string>;
};


auto operator""_url(const char16_t* string, size_t length) -> std::unique_ptr<url::detail::url_t>;
