#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_SECTION_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_SECTION_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_section_element;}
namespace html::elements {class html_table_section_element_private;}


namespace html::elements {class html_table_row_element;}


class html::elements::html_table_section_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_section_element);
    MAKE_PIMPL(html_table_section_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto insert_row(ext::number<long> index = -1) -> html_table_row_element;
    auto delete_row(ext::number<long> index = -1) -> html_table_row_element;

private js_properties:
    DEFINE_GETTER(rows, ranges::any_helpful_view<html_table_row_element*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_SECTION_ELEMENT_HPP
