#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_data_element;}
namespace html::elements {class html_data_element_private;}


class html::elements::html_data_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_data_element);
    MAKE_PIMPL(html_data_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(value, ext::string_view);
    DEFINE_SETTER(value, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_ELEMENT_HPP
