#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_source_element;}


class html::elements::html_source_element
        : public html_element
{
public constructors:
    html_source_element();

public js_properties:
    ext::property<ext::string, _T> src;
    ext::property<ext::string, _T> type;
    ext::property<ext::string, _T> srcset;
    ext::property<ext::string, _T> sizes;
    ext::property<ext::string, _T> media;
    ext::property<ext::number<ulong>, _T> width;
    ext::property<ext::number<ulong>, _T> height;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP
