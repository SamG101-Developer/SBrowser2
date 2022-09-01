#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WINDOW_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WINDOW_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"


namespace html::detail
{
    auto window_open_steps(
            ext::string_view url,
            ext::string_view target,
            ext::string_view features)
            -> void;

    auto tokenize_features_argument(
            ext::string_view features)
            -> ext::vector_view<ext::string>;

    auto check_if_window_feature_is_set(
            ext::vector_view<ext::string> tokenized_features,
            ext::string_view feature_name,
            ext::boolean&& default_value)
            -> ext::boolean;

    auto check_if_popup_window_is_requested(
            ext::vector_view<ext::string> tokenized_features)
            -> ext::boolean;

    auto is_feature_separator(
            char32_t code_point)
            -> ext::boolean;

    auto parse_boolean_feature(
            ext::string_view value)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WINDOW_INTERNALS_HPP
