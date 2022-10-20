#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_LIST_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_LIST_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_data_list_element;}
namespace html::elements {class html_data_list_element_private;}

#include "ext/ranges.hpp"


class html::elements::html_data_list_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_data_list_element);
    MAKE_PIMPL(html_data_list_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(options, ranges::any_helpful_view<html_element>);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_LIST_ELEMENT_HPP
