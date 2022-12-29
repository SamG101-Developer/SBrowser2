#ifndef SBROWSER2_HTML_BODY_ELEMENT_HPP
#define SBROWSER2_HTML_BODY_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_body_element;}
namespace html::elements {class html_body_element_private;}


class html::elements::html_body_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_body_element);
    MAKE_PIMPL(html_body_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_HTML_BODY_ELEMENT_HPP
