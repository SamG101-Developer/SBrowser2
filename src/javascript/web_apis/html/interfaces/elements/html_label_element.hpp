#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_label_element;}
namespace html::elements {class html_label_element_private;}

namespace html::elements {class html_form_element;}


class html::elements::html_label_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_label_element);
    MAKE_PIMPL(html_label_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(form, html_form_element*);
    DEFINE_GETTER(control, html_element*);
    DEFINE_GETTER(html_for, ext::string_view);

    DEFINE_SETTER(html_for, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_HPP
