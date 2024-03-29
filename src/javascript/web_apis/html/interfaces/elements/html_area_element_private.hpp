#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)


DEFINE_PRIVATE_CLASS(html::elements, html_area_element) : html_element_private
{
    ext::string alt;
    ext::string coords;
    detail::area_shape_t shape;
    ext::string href;
    ext::string target;
    ext::string download;
    ext::string ping;
    ext::string rel;
    referrer_policy::detail::referrer_policy_t referrer_policy;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AREA_ELEMENT_PRIVATE_HPP
