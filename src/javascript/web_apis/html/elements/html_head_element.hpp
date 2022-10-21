#ifndef SBROWSER2_HTML_HEAD_ELEMENT_HPP
#define SBROWSER2_HTML_HEAD_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_head_element;}
namespace html::elements {class html_head_element_private;}


class html::elements::html_head_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_head_element);
    MAKE_PIMPL(html_head_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_HTML_HEAD_ELEMENT_HPP
