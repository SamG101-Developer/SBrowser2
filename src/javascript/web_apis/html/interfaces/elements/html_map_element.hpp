#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MAP_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MAP_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_map_element;}
namespace html::elements {class html_map_element_private;}




class html::elements::html_map_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_map_element);
    MAKE_PIMPL(html_map_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(areas, ranges::any_helpful_view<dom::nodes::element*>);

    DEFINE_SETTER(name, ext::string);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MAP_ELEMENT_HPP
