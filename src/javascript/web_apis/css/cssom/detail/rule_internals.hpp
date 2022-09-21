#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_RULE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_RULE_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(css/cssom)


namespace css::detail
{
    auto parse_css_rule(
            ext::string_view string)
            -> css_rule_private;

    auto serialize_css_rule(
            const css_rule_private& rule)
            -> ext::string;

    auto insert_css_rule(
            const css_rule_private& rule,
            ext::vector<css_rule_private*> list,
            ext::number<int> index)
            -> void;

    auto remove_css_rule(
            ext::vector<css_rule_private*> list,
            ext::number<int> index)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_RULE_INTERNALS_HPP
