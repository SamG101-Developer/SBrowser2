#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_HPP

#include "dom_object.hpp"
namespace css::cssom::rules {class css_rule;}

namespace css::cssom::rules {class css_style_sheet;}


class css::cssom::rules::css_rule
        : public dom_object
{
public constructors:
    css_rule();

public js_static_constants:
    constexpr static const ext::number<ushort> STYLE_RULE = 1;
    constexpr static const ext::number<ushort> CHARSET_RULE = 2;
    constexpr static const ext::number<ushort> IMPORT_RULE = 3;
    constexpr static const ext::number<ushort> MEDIA_RULE = 4;
    constexpr static const ext::number<ushort> FONT_FACE_RULE = 5;
    constexpr static const ext::number<ushort> PAGE_RULE = 6;
    constexpr static const ext::number<ushort> MARGIN_RULE = 9;
    constexpr static const ext::number<ushort> NAMESPACE_RULE = 10;

public js_properties:
    ext::property<ext::string> css_text;
    ext::property<css_rule*> parent_rule;
    ext::property<css_style_sheet*> parent_style_sheet;

    ext::property<ext::number<ushort>> type;

protected cpp_accessors:
    virtual DEFINE_GETTER(type) = 0;

private cpp_accessors:
    DEFINE_GETTER(css_text);
    DEFINE_GETTER(parent_rule);
    DEFINE_GETTER(parent_style_sheet);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_HPP
