#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_MARGIN_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_MARGIN_RULE_HPP

#include "css/cssom/rules/css_rule.hpp"
namespace css::cssom::rules {class css_margin_rule;}

namespace css::cssom::other {class css_style_declaration;}


class css::cssom::rules::css_margin_rule
        : public css_rule
{
public constructors:
    css_margin_rule();

public js_properties:
    ext::property<ext::string> name;
    ext::property<std::unique_ptr<other::css_style_declaration>> style;

private cpp_accessors:
    DEFINE_GETTER(type) {return MARGIN_RULE;};
    DEFINE_GETTER(name);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_MARGIN_RULE_HPP
