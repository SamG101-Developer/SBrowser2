#ifndef SBROWSER2_HTML_UNKNOWN_ELEMENT_HPP
#define SBROWSER2_HTML_UNKNOWN_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_unknown_element;}
namespace html::elements {class html_unknown_element_private;}


class html::elements::html_unknown_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_unknown_element);
    MAKE_PIMPL(html_unknown_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_HTML_UNKNOWN_ELEMENT_HPP
