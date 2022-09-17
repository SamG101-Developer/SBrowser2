#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ANCHOR_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ANCHOR_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/html_hyperlink_element_utils.hpp"
namespace html::elements {class html_anchor_element;}


class html::elements::html_anchor_element
        : public html_element
        , public mixins::html_hyperlink_element_utils
{
public constructors:
    html_anchor_element();

public js_properties:
    ext::property<ext::string> target;
    ext::property<ext::string> download;
    ext::property<ext::string> ping;
    ext::property<ext::string> rel;
    ext::property<ext::string> hreflang;
    ext::property<ext::string> type;
    ext::property<ext::string> text;
    ext::property<ext::string> referrer_policy;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(text);
    DEFINE_CUSTOM_SETTER(text);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ANCHOR_ELEMENT_HPP
