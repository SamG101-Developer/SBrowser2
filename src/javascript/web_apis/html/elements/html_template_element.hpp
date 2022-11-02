#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_template_element;}
namespace html::elements {class html_template_element_private;}

namespace dom::nodes {class document_fragment;}


class html::elements::html_template_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_template_element);
    MAKE_PIMPL(html_template_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(content, dom::nodes::document_fragment*);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_HPP
