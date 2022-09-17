#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_RULE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_RULE_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(css/cssom)


namespace css::detail
{
    auto parse_css_rule(
            ext::string_view string)
            -> css_rule_t;

    auto serialize_css_rule(
            const css_rule_t& rule)
            -> ext::string;

    auto insert_css_rule(
            const css_rule_t& rule,
            ext::vector<css_rule_t*> list,
            ext::number<int> index)
            -> void;

    auto remove_css_rule(
            ext::vector<css_rule_t*> list,
            ext::number<int> index)
            -> void;
}


struct css::detail::css_rule_t
{
    const ext::number<int> type;
    ext::string text;

    css_rule_t* parent_rule;
    css_style_sheet_t* parent_css_style_sheet;
    ext::vector<css_rule_t*> child_css_rules;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_RULE_INTERNALS_HPP
