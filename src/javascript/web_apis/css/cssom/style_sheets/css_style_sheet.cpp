#include "css_style_sheet.hpp"
#include "css/css_syntax/_typedefs.hpp"
#include "style_sheet.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "css/cssom/detail/style_sheet_internals.hpp"
#include "css/css_syntax/detail/parsing_internals.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include <range/v3/action/remove_if.hpp>


css::cssom::style_sheets::css_style_sheet::css_style_sheet(
        detail::css_style_sheet_init_t&& options)
{
    bind_get(css_rules);
}


auto css::cssom::style_sheets::css_style_sheet::insert_rule(
        ext::string_view rule,
        ext::number<ulong> index)
        -> ext::number<ulong>
{
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [origin_clean = m_style_sheet->origin_clean_flag] {return !origin_clean;},
            "CSSStyleSheet must have a clean origin");

    dom::detail::throw_v8_exception<NOT_ALLOWED_ERR>(
            [disallow_modifications = m_style_sheet->disallow_modifications_flag] {return !disallow_modifications;},
            "Not allowed to modify the CSSStyleSheet");

    using namespace ext::literals;
    auto parsed_rules = detail::parse_rule(rule);
    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [&parsed_rules, constructed = m_style_sheet->constructed_flag]
            {
                return constructed && parsed_rules.has_value()
                        && parsed_rules->at(0)[ext::tag<1>()].starts_with("@import");
            },
            "Cannot parse an @import rule if the style sheet is already constructed"); // TODO

    return parsed_rules.has_value() && !parsed_rules->empty() // TODO : && !empty() ?
            ? detail::insert_css_rule(parsed_rules->at(0), &m_style_sheet->css_rules)
            : -1; // TODO
}


auto css::cssom::style_sheets::css_style_sheet::delete_rule(
        ext::number<ulong> index)
        -> void
{
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [origin_clean = m_style_sheet->origin_clean_flag] {return !origin_clean;},
            "CSSStyleSheet must have a clean origin");

    dom::detail::throw_v8_exception<NOT_ALLOWED_ERR>(
            [disallow_modifications = m_style_sheet->disallow_modifications_flag] {return !disallow_modifications;},
            "Not allowed to modify the CSSStyleSheet");

    detail::remove_css_rule(index, &m_style_sheet->css_rules);
}


auto css::cssom::style_sheets::css_style_sheet::replace(
        ext::string_view text)
        -> ext::promise<css_style_sheet*>
{
    auto promise = ext::promise<css_style_sheet*>{};
    if (!m_style_sheet->constructed_flag || m_style_sheet->disallow_modifications_flag)
        return promise.reject(dom::other::dom_exception{"", NOT_ALLOWED_ERR});

    m_style_sheet->disallow_modifications_flag = true;

    GO [this, text, &promise]
    {
        auto rules = detail::parse_list_of_rules(text).value_or(detail::parse_result_t::value_type{});
        rules |= ranges::actions::remove_if([](detail::parse_result_t::value_type::value_type& token) {return token[ext::tag<1>()].starts_with("@import");});
        m_style_sheet->css_rules = rules;
        m_style_sheet->disallow_modifications_flag = false;
        promise.resolve(this);
    };

    return promise;
}


auto css::cssom::style_sheets::css_style_sheet::replace_sync(
        ext::string_view text)
        -> void
{
    auto promise = ext::promise<css_style_sheet*>{};
    dom::detail::throw_v8_exception<NOT_ALLOWED_ERR>(
            [style_sheet = m_style_sheet.get()]
            {
                return !style_sheet->constructed_flag || style_sheet->disallow_modifications_flag;
            },
            "");

    auto rules = detail::parse_list_of_rules(text).value_or(detail::parse_result_t::value_type{});
    rules |= ranges::actions::remove_if([](detail::parse_result_t::value_type::value_type& token) {return token[ext::tag<1>()].starts_with("@import");});
    m_style_sheet->css_rules = rules;
}
