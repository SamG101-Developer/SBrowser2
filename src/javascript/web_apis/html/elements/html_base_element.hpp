#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_base_element;}

#include USE_INNER_TYPES(url)

class html::elements::html_base_element
        : html_element
{
public constructors:
    html_base_element();

public js_properties:
    ext::property<ext::string> href;
    ext::property<ext::string> target;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    url::detail::url_t m_frozen_base_url;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(href);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_HPP
