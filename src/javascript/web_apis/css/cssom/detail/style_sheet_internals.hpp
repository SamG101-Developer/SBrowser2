#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_STYLE_SHEET_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_STYLE_SHEET_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(css/cssom)
#include USE_INNER_TYPES(url)

namespace dom::nodes {class document;}
namespace dom::nodes {class node;}


namespace css::detail
{
}


struct css::detail::css_style_sheet_t
{
    ext::string type;
    ext::string location;
    ext::string title;

    css_style_sheet_t* parent;
    css_rule_t* owner_rule;
    dom::nodes::node* owner_node;
    dom::nodes::document* constructor_document;

    ext::vector<ext::string> media;
    ext::boolean alternate_flag;
    ext::boolean disabled_flag;
    ext::boolean constructed_flag;
    ext::boolean disallow_modifications_flag;

    ext::vector<css_rule_t*> css_rules;
    std::unique_ptr<url::detail::url_t> stylesheet_base_url;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_STYLE_SHEET_INTERNALS_HPP
