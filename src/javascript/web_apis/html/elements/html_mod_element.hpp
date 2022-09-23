#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MOD_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MOD_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_mod_element;}


class html::elements::html_mod_element
        : public html_element
{
public constructors:
    html_mod_element();

private js_properties:
    ext::property<ext::string, true> cite;
    ext::property<ext::string, true> date_time;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MOD_ELEMENT_HPP
