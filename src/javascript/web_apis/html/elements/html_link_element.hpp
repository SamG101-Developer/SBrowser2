#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_link_element;}


class html::elements::html_link_element
        : public html_element
{
public constructors:
    html_link_element();

public js_properties:
    ext::property<ext::string, _T> href;
    ext::property<ext::string, _T> cross_origin;
    ext::property<ext::string, _T> rel;
    ext::property<ext::string, _T> as;
    ext::property<ext::string, _T> media;
    ext::property<ext::string, _T> integrity;
    ext::property<ext::string, _T> hreflang;
    ext::property<ext::string, _T> type;
    ext::property<ext::string, _T> image_srcset;
    ext::property<ext::string, _T> image_sizes;
    ext::property<ext::string, _T> referrer;
    ext::property<ext::boolean, _T> disabled;

    ext::property<ext::vector<ext::string>*> rel_list;
    ext::property<ext::vector<ext::string>*> sizes;
    ext::property<ext::vector<ext::string>*> blocking;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean explicitly_enabled;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP
