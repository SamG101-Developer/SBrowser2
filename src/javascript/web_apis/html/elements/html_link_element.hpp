#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_link_element;}

#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(referrer_policy)


class html::elements::html_link_element
        : public html_element
{
public constructors:
    html_link_element();

public js_properties:
    ext::property<ext::string, true> href;
    ext::property<ext::string, true> cross_origin;
    ext::property<detail::rel_t, true> rel;
    ext::property<ext::string, true> as;
    ext::property<ext::string, true> media;
    ext::property<ext::string, true> integrity;
    ext::property<ext::string, true> hreflang;
    ext::property<ext::string, true> type;
    ext::property<ext::string, true> image_srcset;
    ext::property<ext::string, true> image_sizes;
    ext::property<referrer_policy::detail::referrer_policy_t, true> referrer;
    ext::property<ext::boolean, true> disabled;

    ext::property<ext::vector<ext::string>*> sizes;
    ext::property<ext::vector<ext::string>*> blocking;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean explicitly_enabled;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP
