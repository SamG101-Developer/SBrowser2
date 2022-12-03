#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"

#include "ext/ranges.hpp"
namespace html::elements {class html_table_caption_element;}
namespace html::elements {class html_table_caption_element_private;}
namespace html::elements {class html_table_section_element;}
namespace html::elements {class html_table_section_element_private;}
namespace html::elements {class html_table_row_element;}


DEFINE_PRIVATE_CLASS(html::elements, html_table_element) : html::elements::html_element_private
{
    template <typename T>
    auto table_children(ext::string&& local_name = u8"*") const -> ranges::any_helpful_view<T*>;

    template <typename ...Types>
    auto table_children(ext::string&& local_name = u8"*") const -> ranges::any_helpful_view<html_element*> requires (sizeof...(Types) > 1);

    ranges::any_helpful_view<html_table_caption_element*> t_captions = child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_caption_element*>;
            // | ranges::views::filter_eq(&html_table_caption_element_private::local_name, u8"caption", ext::get_pimpl);

    ranges::any_helpful_view<html_table_section_element*> t_heads = child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_section_element*>;
            // | ranges::views::filter_eq(&html_table_section_element_private::local_name, u8"thead", ext::get_pimpl);

    ranges::any_helpful_view<html_table_section_element*> t_footers = child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_section_element*>;
            // | ranges::views::filter_eq(&html_table_section_element_private::local_name, u8"thead", ext::get_pimpl);

    ranges::any_helpful_view<html_table_section_element*> t_bodies = child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_section_element*>;
            // | ranges::views::filter_eq(&html_table_section_element_private::local_name, u8"tbody", ext::get_pimpl);

    ranges::any_helpful_view<html_table_row_element*> t_rows = child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_row_element*>;
            // | ranges::views::filter_eq(&html_table_row_element_private::local_name, u8"tr", ext::get_pimpl);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP
