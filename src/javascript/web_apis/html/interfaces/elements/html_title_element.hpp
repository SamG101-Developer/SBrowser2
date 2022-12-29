#ifndef SBROWSER2_HTML_TITLE_ELEMENT_HPP
#define SBROWSER2_HTML_TITLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_title_element;}
namespace html::elements {class html_title_element_private;}


class html::elements::html_title_element
        : public html::elements::html_element
{
public constructors:
    DOM_CTORS(html_title_element);
    MAKE_PIMPL(html_title_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(text, ext::string);
    DEFINE_SETTER(text, ext::string);
};


#endif //SBROWSER2_HTML_TITLE_ELEMENT_HPP
