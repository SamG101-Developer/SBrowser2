#ifndef SBROWSER2_HTML_HTML_ELEMENT_HPP
#define SBROWSER2_HTML_HTML_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_html_element;}
namespace html::elements {class html_html_element_private;}


class html::elements::html_html_element
        : public html::elements::html_element
{
public constructors:
    DOM_CTORS(html_html_element);
    MAKE_PIMPL(html_html_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_HTML_HTML_ELEMENT_HPP
