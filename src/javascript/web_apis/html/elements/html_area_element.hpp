#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/html_hyperlink_element_utils.hpp"
namespace html::elements {class html_area_element;}

#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(referrer_policy)


class html::elements::html_area_element
        : public html_element
        , public mixins::html_hyperlink_element_utils
{
public constructors:
    DOM_CTORS(html_area_element);
    html_area_element();

public js_properties:
    ext::property<ext::string> alt;
    ext::property<ext::string> coords;
    ext::property<detail::area_shape_t> shape;
    ext::property<ext::string> target;
    ext::property<ext::string> download;
    ext::property<ext::string> ping;
    ext::property<ext::string> rel;
    ext::property<referrer_policy::detail::referrer_policy_t> referrer_policy;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_HPP
