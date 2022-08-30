#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_element;}

namespace html::elements {class html_table_caption_element;}
namespace html::elements {class html_table_section_element;}
namespace html::elements {class html_table_row_element;}


class html::elements::html_table_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_element);
    html_table_element();

public js_methods:
    auto create_caption() -> html_table_caption_element;
    auto delete_caption() -> html_table_caption_element*;

    auto create_t_head() -> html_table_section_element;
    auto delete_t_head() -> html_table_section_element*;

    auto create_t_foot() -> html_table_section_element;
    auto delete_t_foot() -> html_table_section_element*;

    auto create_t_body() -> html_table_section_element;

    auto insert_row(const ext::number<long> index = -1) -> html_table_row_element;
    auto delete_row(const ext::number<long> index = -1) -> html_table_row_element;

public js_properties:
    ext::property<std::unique_ptr<html_table_caption_element>> caption;
    ext::property<std::unique_ptr<html_table_section_element>> t_head;
    ext::property<std::unique_ptr<html_table_section_element>> t_foot;
    ext::property<std::unique_ptr<ext::vector<html_table_section_element*>>> t_bodies;
    ext::property<std::unique_ptr<ext::vector<html_table_row_element*>>> rows;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_HPP
