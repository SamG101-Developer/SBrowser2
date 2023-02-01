#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_dialog_element;}
namespace html::elements {class html_dialog_element_private;}


class html::elements::html_dialog_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_dialog_element);
    MAKE_PIMPL(html_dialog_element);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto show() -> void;
    auto show_modal() -> void;
    auto close(ext::string&& return_value = u8"") -> void;

private js_properties:
    DEFINE_GETTER(open, ext::boolean);
    DEFINE_GETTER(return_value, ext::string_view);

    DEFINE_SETTER(open, ext::boolean);
    DEFINE_SETTER(return_value, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_HPP
