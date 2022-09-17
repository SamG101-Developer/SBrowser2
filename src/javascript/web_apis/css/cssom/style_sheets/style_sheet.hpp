#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLESHEET_STYLE_SHEET_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLESHEET_STYLE_SHEET_HPP

#include "dom_object.hpp"
namespace css::cssom::style_sheets {class style_sheet;}

#include USE_INNER_TYPES(css/cssom)
namespace css::cssom::style_sheets {class css_style_sheet;}
namespace dom::nodes {class element;}
namespace dom::nodes {class processing_instruction;}


class css::cssom::style_sheets::style_sheet
        : public dom_object
{
public constructors:
    style_sheet();

public js_properties:
    ext::property<ext::string> type;
    ext::property<ext::string> href;
    ext::property<ext::string> title;

    ext::property<dom::nodes::node*> owner_node;
    ext::property<css_style_sheet*> parent_style_sheet;
    ext::property<ext::vector<ext::string>> media;
    ext::property<ext::boolean> disabled;

protected cpp_properties:
    std::unique_ptr<detail::css_style_sheet_t> m_style_sheet;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(type);
    DEFINE_CUSTOM_GETTER(href);
    DEFINE_CUSTOM_GETTER(title);
    DEFINE_CUSTOM_GETTER(owner_node);
    DEFINE_CUSTOM_GETTER(parent_style_sheet);
    DEFINE_CUSTOM_GETTER(media);
    DEFINE_CUSTOM_GETTER(disabled);

    DEFINE_CUSTOM_SETTER(disabled);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLESHEET_STYLE_SHEET_HPP
