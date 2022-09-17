#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_PAGE_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_PAGE_RULE_HPP

#include "css/cssom/rules/css_grouping_rule.hpp"
namespace css::cssom::rules {class css_style_rule;}

namespace css::cssom::other {class css_style_declaration;}


class css::cssom::rules::css_style_rule
        : public css_grouping_rule
{
public constructors:
    css_style_rule();

public js_properties:
    ext::property<ext::string> selector_text;
    ext::property<std::unique_ptr<other::css_style_declaration>> style;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(type) override {return PAGE_RULE;}
    DEFINE_CUSTOM_GETTER(selector_text);
    DEFINE_CUSTOM_SETTER(selector_text);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_PAGE_RULE_HPP
