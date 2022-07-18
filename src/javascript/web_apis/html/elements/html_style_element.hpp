#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_style_element;}


class html::elements::html_style_element
        : public html_element
{
public constructors:
    html_style_element();

public js_properties:
    ext::property<bool, _F> disabled;
    ext::property<ext::string, _T> media;
    ext::property<ext::vector<ext::string>*, _F> blocking;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    auto get_disabled() const -> bool;
    auto set_disabled(bool val) -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP
