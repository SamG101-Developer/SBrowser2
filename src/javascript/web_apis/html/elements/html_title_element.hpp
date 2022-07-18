#ifndef SBROWSER2_HTML_TITLE_ELEMENT_HPP
#define SBROWSER2_HTML_TITLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_title_element;}


class html::elements::html_title_element
        : public html::elements::html_element
{
public constructors:
    html_title_element();

public js_properties:
    ext::property<ext::string, _T> text;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    auto get_text() const -> ext::string;
    auto set_text(ext::string_view val) -> void;
};


#endif //SBROWSER2_HTML_TITLE_ELEMENT_HPP
