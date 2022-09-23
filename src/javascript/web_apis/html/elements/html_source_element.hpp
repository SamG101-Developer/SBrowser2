#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_source_element;}


class html::elements::html_source_element
        : public html_element
{
public constructors:
    html_source_element();

private js_properties:
    ext::property<ext::string, true> src;
    ext::property<ext::string, true> type;
    ext::property<ext::string, true> srcset;
    ext::property<ext::string, true> sizes;
    ext::property<ext::string, true> media;
    ext::property<ext::number<ulong>, true> width;
    ext::property<ext::number<ulong>, true> height;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP
