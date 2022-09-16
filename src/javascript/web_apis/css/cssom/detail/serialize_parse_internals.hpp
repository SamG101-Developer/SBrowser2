#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_SERIALIZE_PARSE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_SERIALIZE_PARSE_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(css/media_queries)


namespace css::detail
{
    auto escape_character(
            char character)
            -> ext::string;

    auto escape_character_as_code_point(
            char character)
            -> ext::string;

    auto serialize_identifier(
            ext::string_view identifier)
            -> ext::string;

    auto serialize_string(
            ext::string_view string)
            -> ext::string;

    auto serialize_url(
            ext::string_view url)
            -> ext::string;

    auto serialize_local(
            ext::string_view local)
            -> ext::string;

    auto serialize_comma_separated_list(
            ext::vector_view<ext::string_view> list)
            -> ext::string;

    auto serialize_whitespace_separated_list(
            ext::vector_view<ext::string_view> list)
            -> ext::string;

    auto serialize_media_query_list(
            const media_queries_t&)
            -> ext::string;

    auto serialize_media_query(
            const media_queries_t&)
            -> ext::string;

    auto serialize_media_feature(
            ext::string_view feature)
            -> ext::string;

    auto serialize_group_of_selectors(
            ext::vector_view<selector_t*> selectors)
            -> ext::string;

    auto serialize_selector(
            const selector_t& selector)
            -> ext::string;

    auto serialize_simple_selector(
            const selector_t& selector)
            -> ext::string;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_SERIALIZE_PARSE_INTERNALS_HPP
