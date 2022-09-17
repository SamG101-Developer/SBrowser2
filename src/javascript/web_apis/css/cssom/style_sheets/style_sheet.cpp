#include "style_sheet.hpp"

#include "css/cssom/detail/style_sheet_internals.hpp"
#include "url/detail/url_internals.hpp"


css::cssom::style_sheets::style_sheet::style_sheet()
{
    bind_get(type);
    bind_get(href);
    bind_get(owner_node);
    bind_get(parent_style_sheet);
    bind_get(title);
    bind_get(media);
}


auto css::cssom::style_sheets::style_sheet::get_type() const -> typename decltype(this->type)::value_t
{return m_style_sheet->type;}


auto css::cssom::style_sheets::style_sheet::get_href() const -> typename decltype(this->href)::value_t
{return m_style_sheet->location;}


auto css::cssom::style_sheets::style_sheet::get_owner_node() const -> typename decltype(this->owner_node)::value_t
{return m_style_sheet->owner_node;}


auto css::cssom::style_sheets::style_sheet::get_parent_style_sheet() const -> typename decltype(this->parent_style_sheet)::value_t
{return m_style_sheet->parent;}


auto css::cssom::style_sheets::style_sheet::get_title() const -> typename decltype(this->title)::value_t
{return m_style_sheet->title;}


auto css::cssom::style_sheets::style_sheet::get_media() const -> typename decltype(this->media)::value_t
{return m_style_sheet->media;}
