#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_HPP

#include "dom_object.hpp"
namespace css::cssom::rules {class css_rule;}

#include "css/cssom/rules/css_rule_private.hpp"
#include INCLUDE_INNER_TYPES(css/cssom)
namespace css::cssom::rules {class css_style_sheet;}


class css::cssom::rules::css_rule
        : public virtual dom_object
{
public constructors:
    css_rule();

public js_static_constants:
    /* [CSSOM] */
    constexpr static const ext::number<ushort> STYLE_RULE = 1;
    constexpr static const ext::number<ushort> CHARSET_RULE = 2;
    constexpr static const ext::number<ushort> IMPORT_RULE = 3;
    constexpr static const ext::number<ushort> MEDIA_RULE = 4;
    constexpr static const ext::number<ushort> FONT_FACE_RULE = 5;
    constexpr static const ext::number<ushort> PAGE_RULE = 6;

    /* [CSS-ANIMATIONS] */
    constexpr static const ext::number<ushort> KEYFRAMES_RULE = 7;
    constexpr static const ext::number<ushort> KEYFRAME_RULE = 8;

    /* [CSSOM] */
    constexpr static const ext::number<ushort> MARGIN_RULE = 9;
    constexpr static const ext::number<ushort> NAMESPACE_RULE = 10;

private js_properties:
    ext::property<ext::string> css_text;
    ext::property<css_rule*> parent_rule;
    ext::property<css_style_sheet*> parent_style_sheet;

    ext::property<ext::number<ushort>> type;

private cpp_members:
    MAKE_PIMPL(css_rule);
    MAKE_V8_AVAILABLE;

protected cpp_accessors:
    virtual DEFINE_CUSTOM_GETTER(type) = 0;

private js_properties:
    DEFINE_CUSTOM_GETTER(css_text);
    DEFINE_CUSTOM_GETTER(parent_rule);
    DEFINE_CUSTOM_GETTER(parent_style_sheet);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_RULES_CSS_RULE_HPP
