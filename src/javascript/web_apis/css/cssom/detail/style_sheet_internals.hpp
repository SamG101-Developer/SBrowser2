#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_STYLE_SHEET_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_STYLE_SHEET_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(css/cssom)
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)

namespace dom::nodes {class document;}
namespace dom::nodes {class node;}


namespace css::detail
{
    auto create_css_style_sheet()
            -> css_style_sheet_private;

    auto add_css_style_sheet()
            -> void;

    auto remove_css_style_sheet(
            const css_style_sheet_private& style_sheet)
            -> void;

    auto persistent_css_style_sheet(
            const css_style_sheet_private& style_sheet)
            -> ext::boolean;

    auto is_css_style_sheet_set(
            const ext::set<css_style_sheet_private*>& style_sheets)
            -> ext::boolean;

    auto css_style_sheet_set_name(
            const ext::set<css_style_sheet_private*>& style_sheets)
            -> ext::string_view;

    auto enable_style_sheet_set(
            ext::string_view name)
            -> void;

    auto select_style_sheet_set(
            ext::string_view name)
            -> void;

    auto change_preferred_css_style_sheet_set_name(
            ext::string_view name)
            -> void;

    auto fetch_css_style_sheets(
            const url::detail::url_t& parsed_url,
            ext::variant<fetch::detail::referrer_t, url::detail::url_t*> referrer,
            dom::nodes::node* document,
            ext::set<ext::string> parameters)
            -> void;

    auto associated_css_style_sheet(
            dom::nodes::node* node)
            -> css_style_sheet_private&;

    ext::string last_css_style_sheet_set_name; // TODO : global variable :(
    ext::string preferred_css_style_sheet_set_name; // TODO : global variable :(
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_STYLE_SHEET_INTERNALS_HPP
