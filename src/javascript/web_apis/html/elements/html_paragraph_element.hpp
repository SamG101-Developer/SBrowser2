#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PARAGRAPH_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PARAGRAPH_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_paragraph_element;}
namespace html::elements {class html_paragraph_element_private;}


class html::elements::html_paragraph_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_paragraph_element);
    MAKE_PIMPL(html_paragraph_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PARAGRAPH_ELEMENT_HPP
