#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_base_element;}
namespace html::elements {class html_base_element_private;}


class html::elements::html_base_element
        : html_element
{
public constructors:
    DOM_CTORS(html_base_element);
    MAKE_PIMPL(html_base_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(href, ext::string_view);
    DEFINE_GETTER(target, ext::string_view);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(target, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_HPP
