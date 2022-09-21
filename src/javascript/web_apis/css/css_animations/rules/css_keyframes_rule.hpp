#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_RULES_CSS_KEYFRAMES_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_RULES_CSS_KEYFRAMES_RULE_HPP

#include "css/cssom/rules/css_rule.hpp"
namespace css::css_animations::rules {class css_keyframes_rule;}

namespace css::css_animations::rules {class css_keyframe_rule;}


class css::css_animations::rules::css_keyframes_rule
        : public cssom::rules::css_rule
{
public constructors:
    css_keyframes_rule() = default;

public js_methods:
    auto append_rule(ext::string_view rule) -> void;
    auto delete_rule(ext::string_view select) -> void;
    auto find_rule(ext::string_view select) -> css_keyframe_rule*;

public js_properties:
    ext::property<ext::string> name;
    ext::property<ext::vector<cssom::rules::css_rule*>> css_rules;

private cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_RULES_CSS_KEYFRAMES_RULE_HPP
