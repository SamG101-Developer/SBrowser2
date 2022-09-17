#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_IMPORT_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_IMPORT_RULE_HPP

#include "css/cssom/rules/css_rule.hpp"
namespace css::cssom::rules {class css_import_rule;}

namespace css::cssom::style_sheets {class css_style_sheet;}


class css::cssom::rules::css_import_rule
        : public css_rule
{
public constructors:
    css_import_rule();

public js_properties:
    ext::property<ext::string> href;
    ext::property<ext::vector<ext::string>> media;
    ext::property<style_sheets::css_style_sheet*> style_sheet;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(href);
    DEFINE_CUSTOM_GETTER(media);
    DEFINE_CUSTOM_GETTER(style_sheet);
    DEFINE_CUSTOM_GETTER(type) override {return IMPORT_RULE;}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_IMPORT_RULE_HPP
