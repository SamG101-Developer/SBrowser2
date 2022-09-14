#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WINDOW_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WINDOW_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(url)
namespace dom::nodes {class window;}


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
            ext::boolean default_value)
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

    auto set_up_window_environment_settings_object(
            const url::detail::url_t& url,
            v8::Local<v8::Context> execution_context,
            v8::Isolate* reserved_environment,
            const url::detail::url_t& top_level_creation_url,
            const detail::origin_t& top_level_origin)
            -> dom::nodes::window;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_WINDOW_INTERNALS_HPP
