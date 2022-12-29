#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/html_hyperlink_element_utils.hpp"
namespace html::elements {class html_area_element;}
namespace html::elements {class html_area_element_private;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)


class html::elements::html_area_element
        : public html_element
        , public mixins::html_hyperlink_element_utils
{
public constructors:
    DOM_CTORS(html_area_element);
    MAKE_PIMPL(html_area_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(alt, ext::string_view);
    DEFINE_GETTER(coords, ext::string_view);
    DEFINE_GETTER(shape, detail::area_shape_t);
    DEFINE_GETTER(target, ext::string_view);
    DEFINE_GETTER(download, ext::string_view);
    DEFINE_GETTER(ping, ext::string_view);
    DEFINE_GETTER(rel, ext::string_view);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);

    DEFINE_SETTER(alt, ext::string);
    DEFINE_SETTER(coords, ext::string);
    DEFINE_SETTER(shape, detail::area_shape_t);
    DEFINE_SETTER(target, ext::string);
    DEFINE_SETTER(download, ext::string);
    DEFINE_SETTER(ping, ext::string);
    DEFINE_SETTER(rel, ext::string);
    DEFINE_SETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_HPP
