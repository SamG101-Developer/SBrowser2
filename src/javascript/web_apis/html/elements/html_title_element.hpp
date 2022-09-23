#ifndef SBROWSER2_HTML_TITLE_ELEMENT_HPP
#define SBROWSER2_HTML_TITLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_title_element;}


class html::elements::html_title_element
        : public html::elements::html_element
{
public constructors:
    html_title_element();

private js_properties:
    ext::property<ext::string> text;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private js_properties:
    DEFINE_CUSTOM_GETTER(text);
    DEFINE_CUSTOM_SETTER(text);
};


#endif //SBROWSER2_HTML_TITLE_ELEMENT_HPP
