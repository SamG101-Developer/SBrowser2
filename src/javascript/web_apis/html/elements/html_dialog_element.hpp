#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_dialog_element;}


class html::elements::html_dialog_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_dialog_element);
    html_dialog_element() = default;

public js_methods:
    auto show() -> void;
    auto show_modal() -> void;
    auto close(ext::string&& return_value = "") -> void;

private js_properties:
    ext::property<ext::boolean> open;
    ext::property<ext::string> return_value;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_is_modal_flag;
    html_element* m_previously_focused_element;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_HPP
