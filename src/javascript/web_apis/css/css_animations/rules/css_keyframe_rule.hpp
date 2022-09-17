#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_RULES_CSS_KEYFRAME_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_RULES_CSS_KEYFRAME_RULE_HPP

#include "css/cssom/rules/css_rule.hpp"
namespace css::css_animations::rules {class css_keyframe_rule;}

namespace css::cssom::other {class css_style_declaration;}


class css::css_animations::rules::css_keyframe_rule
        : public cssom::rules::css_rule
{
public constructors:
    css_keyframe_rule() = default;

public js_properties:
    ext::property<ext::string> key_text;
    ext::property<std::unique_ptr<cssom::other::css_style_declaration>> style;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_RULES_CSS_KEYFRAME_RULE_HPP
