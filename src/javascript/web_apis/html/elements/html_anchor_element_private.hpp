#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ANCHOR_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ANCHOR_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(referrer_policy)


DEFINE_PRIVATE_CLASS(html::elements, html_anchor_element) : html_element_private
{
    ext::string target;
    ext::string download;
    ext::string ping;
    ext::string rel;
    ext::string hreflang;
    ext::string type;
    referrer_policy::detail::referrer_policy_t referrer_policy;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ANCHOR_ELEMENT_PRIVATE_HPP
