#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_PRIVATE_HPP

#include "ext/pimpl.ixx"

#include "ext/string.hpp"
#include "ext/vector.hpp"

DECLARE_PRIVATE_CLASS(css::cssom, css_style_sheet)


DEFINE_PRIVATE_CLASS(css::cssom, css_rule)
{
    const ext::number<int> type;
    ext::string text;

    css_rule_private* parent_rule;
    css_style_sheet_private* parent_css_style_sheet;
    ext::vector<css_rule_private*> child_css_rules;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_PRIVATE_HPP
