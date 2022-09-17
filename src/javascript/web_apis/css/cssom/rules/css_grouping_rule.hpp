#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_GROUPING_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_GROUPING_RULE_HPP

#include "css/cssom/rules/css_rule.hpp"
namespace css::cssom::rules {class css_grouping_rule;}


class css::cssom::rules::css_grouping_rule
        : public css_rule
{
public constructors:
    css_grouping_rule();

public js_methods:
    auto insert_rule(ext::string_view rule, ext::number<ulong> index = 0) -> ext::number<ulong>;
    auto delete_rule(ext::number<ulong> index) -> void;

public js_properties:
    ext::property<ext::vector<css_rule*>> css_rules;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_GROUPING_RULE_HPP
