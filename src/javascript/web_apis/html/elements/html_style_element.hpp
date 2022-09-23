#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_style_element;}


class html::elements::html_style_element
        : public html_element
{
public constructors:
    html_style_element();

private js_properties:
    ext::property<ext::boolean> disabled;
    ext::property<ext::string> media;
    ext::property<std::unique_ptr<ext::vector<ext::string>>> blocking;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private js_properties:
    DEFINE_CUSTOM_GETTER(disabled);
    DEFINE_CUSTOM_SETTER(disabled);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP
