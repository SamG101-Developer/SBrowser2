#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DETAILS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DETAILS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_details_element;}
namespace html::elements {class html_details_element_private;}


class html::elements::html_details_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_details_element);
    MAKE_PIMPL(html_details_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(open, ext::boolean);
    DEFINE_SETTER(open, ext::boolean);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DETAILS_ELEMENT_HPP
