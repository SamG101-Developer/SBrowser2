#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LI_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LI_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_li_element;}
namespace html::elements {class html_li_element_private;}


class html::elements::html_li_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_li_element);
    MAKE_PIMPL(html_li_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(value, ext::number<long>);
    DEFINE_SETTER(value, ext::number<long>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LI_ELEMENT_HPP
