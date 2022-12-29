#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_QUOTE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_QUOTE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_quote_element;}
namespace html::elements {class html_quote_element_private;}


class html::elements::html_quote_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_quote_element);
    MAKE_PIMPL(html_quote_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(cite, ext::string_view);
    DEFINE_SETTER(cite, ext::string);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_QUOTE_ELEMENT_HPP
