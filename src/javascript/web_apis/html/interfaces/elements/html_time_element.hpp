#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TIME_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TIME_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_time_element;}
namespace html::elements {class html_time_element_private;}


class html::elements::html_time_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_time_element);
    MAKE_PIMPL(html_time_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(date_time, ext::string_view);
    DEFINE_SETTER(date_time, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TIME_ELEMENT_HPP
