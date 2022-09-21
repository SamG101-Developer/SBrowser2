#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_OTHER_CSS_STYLE_DECLARATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_OTHER_CSS_STYLE_DECLARATION_HPP

#include "dom_object.hpp"
#include "ext/vector_like.hpp"
namespace css::cssom::other {class css_style_declaration;}


#include "css/cssom/other/css_style_declaration_private.hpp"
#include INCLUDE_INNER_TYPES(css/cssom)
namespace css::cssom::rules {class css_rule;}


class css::cssom::other::css_style_declaration
        : public dom_object
        , ext::vector_like_linked<ext::pair<ext::string, ext::string>>
{
public constructors:
    css_style_declaration();

public js_methods:
    auto get_property_value(ext::string_view property) -> ext::string_view;
    auto get_property_priority(ext::string_view property) -> ext::string_view;
    auto set_property_value(ext::string_view property, ext::string&& value, ext::string&& priority) -> void;
    auto remove_property_value(ext::string_view property) -> ext::string_view;

public js_properties:
    ext::property<ext::string> css_text;
    ext::property<ext::string> css_float;
    ext::property<rules::css_rule*> parent_rule;

    // TODO : required?
    ext::property<ext::string> _camel_cased_attribute;
    ext::property<ext::string> _webkit_cased_attribute;
    ext::property<ext::string> _dashed_attribute;

    PUT_FORWARDS(css_text);

private cpp_members:
    MAKE_PIMPL(css_style_declaration);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(css_text);
    DEFINE_CUSTOM_GETTER(css_float);
    DEFINE_CUSTOM_GETTER(parent_rule);

    DEFINE_CUSTOM_SETTER(css_text);
    DEFINE_CUSTOM_SETTER(css_float);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_OTHER_CSS_STYLE_DECLARATION_HPP
