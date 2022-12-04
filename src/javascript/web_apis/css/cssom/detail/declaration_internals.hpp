#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_DECLARATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_DECLARATION_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(css/cssom)
namespace dom::nodes {class element;}


namespace css::detail
{
    auto parse_declaration_block(
            ext::string_view string)
            -> css_declaration_block_t;

    auto serialize_declaration_block(
            ext::string_view property,
            ext::string_view value,
            ext::boolean important_flag = true)
            -> ext::string;

    auto serialize_declaration_block(
            const css_declaration_block_t& block)
            -> ext::string;

    auto update_style_attribute(
            const css_declaration_block_t& block)
            -> void;

    auto preferred_order( // Comparison method for std::sort
            ext::string_view a,
            ext::string_view b)
            -> ext::boolean;

    auto set_css_declaration(
            ext::string_view property,
            ext::vector<ext::string> component_value_list,
            ext::boolean important_flag = true)
            -> void;
}


struct css::detail::css_declaration_t // TODO: attribute change steps?
{
    ext::string property_name;
    ext::vector<ext::string> value;

    ext::boolean important_flag;
    ext::boolean case_sensitive_flag;
};


struct css::detail::css_declaration_block_t
{
    css_declaration_block_t();

    ext::vector<css_declaration_t*> declarations;
    ext::boolean computed_flag = false;
    ext::boolean updating_flag = false;

    css_rule_private* parent_css_rule;
    dom::nodes::element* owner_node;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_DECLARATION_INTERNALS_HPP
