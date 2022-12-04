#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLE_SHEETS_CSS_STYLE_SHEET_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLE_SHEETS_CSS_STYLE_SHEET_HPP

#include "css/cssom/style_sheets/style_sheet.hpp"
namespace css::cssom::style_sheets {class css_style_sheet;}


#include INCLUDE_INNER_TYPES(css/cssom)
namespace css::cssom::rules {class css_rule;}


class css::cssom::style_sheets::css_style_sheet
        : public style_sheet
{
public constructors:
    css_style_sheet(detail::css_style_sheet_init_t&& options = {});

public js_methods:
    auto insert_rule(ext::string_view rule, ext::number<ulong> index = 0) -> ext::number<ulong>;
    auto delete_rule(ext::number<ulong> index) -> void;
    auto replace(ext::string_view text) -> ext::promise<css_style_sheet*>;
    auto replace_sync(ext::string_view text) -> void;

private js_properties:
    ext::property<rules::css_rule*> owner_rule;
    ext::property<ext::vector<rules::css_rule*>> css_rules;

private js_properties:
    DEFINE_CUSTOM_GETTER(css_rules);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_STYLE_SHEETS_CSS_STYLE_SHEET_HPP
