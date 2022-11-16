#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_ENCODING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_ENCODING_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include <bit>

namespace encoding {class encoding;}


namespace url::detail
{
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
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_ENCODING_INTERNALS_HPP
