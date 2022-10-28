#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OLIST_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OLIST_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_olist_element;}
namespace html::elements {class html_olist_element_private;}


class html::elements::html_olist_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_olist_element);
    MAKE_PIMPL(html_olist_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(reversed, ext::boolean);
    DEFINE_GETTER(start, ext::number<long>);
    DEFINE_GETTER(type, ext::string_view);

    DEFINE_SETTER(reversed, ext::boolean);
    DEFINE_SETTER(start, ext::number<long>);
    DEFINE_SETTER(type, ext::string);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OLIST_ELEMENT_HPP
