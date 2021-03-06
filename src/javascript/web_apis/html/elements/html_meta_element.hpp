#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_META_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_META_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_meta_element;}

class html::elements::html_meta_element
        : public html_element
{
public constructors:
    html_meta_element();

public js_properties:
    ext::property<ext::string, _T> name;
    ext::property<ext::string, _T> http_equiv;
    ext::property<ext::string, _T> content;
    ext::property<ext::string, _T> media;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_META_ELEMENT_HPP
