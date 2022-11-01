#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_output_element;}
namespace html::elements {class html_output_element_private;}

namespace html::elements {class html_form_element;}


class html::elements::html_output_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_output_element);
    MAKE_PIMPL(html_output_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(html_for, ext::string_view);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(type, ext::string);
    DEFINE_GETTER(default_value, ext::string);
    DEFINE_GETTER(value, ext::string);
    DEFINE_GETTER(form, html_form_element*);
    DEFINE_GETTER(labels, ext::vector_span<dom::nodes::node*>);

    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(default_value, ext::string);
    DEFINE_SETTER(value, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_HPP
