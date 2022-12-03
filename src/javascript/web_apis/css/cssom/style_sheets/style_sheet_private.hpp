#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLE_SHEETS_STYLE_SHEET_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLE_SHEETS_STYLE_SHEET_PRIVATE_HPP

#include "ext/boolean.ixx"
#include "ext/pimpl.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(url)

DECLARE_PRIVATE_CLASS(css::cssom, css_rule)

namespace dom::nodes {class document;}
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(css::cssom, css_style_sheet)
{
    ext::string type;
    ext::string location;
    ext::string title;

    css_style_sheet_private* parent;
    css_rule_private* owner_rule;
    dom::nodes::node* owner_node;
    dom::nodes::document* constructor_document;

    ext::vector<ext::string> media;
    ext::boolean alternate_flag;
    ext::boolean disabled_flag;
    ext::boolean origin_clean_flag;
    ext::boolean constructed_flag;
    ext::boolean disallow_modifications_flag;

    ext::vector<css_rule_private*> css_rules;
    std::unique_ptr<url::detail::url_t> stylesheet_base_url;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLE_SHEETS_STYLE_SHEET_PRIVATE_HPP
