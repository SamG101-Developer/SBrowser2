#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_element;}
namespace html::elements {class html_table_element_private;}

#include "ext/ranges.hpp"
namespace html::elements {class html_table_caption_element;}
namespace html::elements {class html_table_section_element;}
namespace html::elements {class html_table_row_element;}


class html::elements::html_table_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_element);
    MAKE_PIMPL(html_table_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto create_caption() -> html_table_caption_element*;
    auto create_t_head() -> html_table_section_element*;
    auto create_t_foot() -> html_table_section_element*;
    auto create_t_body() -> html_table_section_element*;
    auto insert_row(ext::number<long> index = -1) -> html_table_row_element*;

    auto delete_t_head() -> html_table_section_element*;
    auto delete_t_foot() -> html_table_section_element*;
    auto delete_caption() -> html_table_caption_element*;
    auto delete_row(ext::number<long> index = -1) -> html_table_row_element*;

private js_properties:
    DEFINE_GETTER(caption, html_table_caption_element*);
    DEFINE_SETTER(caption, std::unique_ptr<html_table_caption_element>&&);
    DEFINE_GETTER(t_head, html_table_section_element*);
    DEFINE_SETTER(t_head, std::unique_ptr<html_table_section_element>&&);
    DEFINE_GETTER(t_foot, html_table_section_element*);
    DEFINE_SETTER(t_foot, std::unique_ptr<html_table_section_element>&&);
    DEFINE_GETTER(t_bodies, ranges::any_helpful_view<html_table_section_element*>);
    DEFINE_GETTER(rows, ranges::any_helpful_view<html_table_row_element*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_HPP
