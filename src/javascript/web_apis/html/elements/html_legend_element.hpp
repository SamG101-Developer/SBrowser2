#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LEGEND_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LEGEND_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_legend_element;}
namespace html::elements {class html_legend_element_private;}

namespace html::elements {class html_form_element;}


class html::elements::html_legend_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_legend_element);
    MAKE_PIMPL(html_legend_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(form, html_form_element*);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LEGEND_ELEMENT_HPP
