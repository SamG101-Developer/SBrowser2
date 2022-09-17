#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_NAMESPACE_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_NAMESPACE_RULE_HPP

#include "css/cssom/rules/css_rule.hpp"
namespace css::cssom::rules {class css_namespace_rule;}


class css::cssom::rules::css_namespace_rule
        : public css_rule
{
public constructors:
    css_namespace_rule();

public js_properties:
    ext::property<ext::string> namespace_uri;
    ext::property<ext::string> prefix;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_NAMESPACE_RULE_HPP
