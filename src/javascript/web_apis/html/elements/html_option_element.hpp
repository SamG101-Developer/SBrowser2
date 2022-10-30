#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_option_element;}
namespace html::elements {class html_option_element_private;}

namespace html::elements {class html_form_element;}


class html::elements::html_option_element
         : public html_element
{
public constructors:
    DOM_CTORS(html_option_element);
    MAKE_PIMPL(html_option_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(form, html_form_element*);
    DEFINE_GETTER(label, ext::string_view);
    DEFINE_GETTER(default_selected, ext::boolean);
    DEFINE_GETTER(selected, ext::boolean);
    DEFINE_GETTER(value, ext::string_view);
    DEFINE_GETTER(text, ext::string);
    DEFINE_GETTER(index, ext::number<long>);

    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(label, ext::string);
    DEFINE_SETTER(default_selected, ext::boolean);
    DEFINE_SETTER(selected, ext::boolean);
    DEFINE_SETTER(value, ext::string);
    DEFINE_SETTER(text, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_HPP
