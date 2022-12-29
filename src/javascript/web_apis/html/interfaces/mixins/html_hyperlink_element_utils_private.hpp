#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(url)


DEFINE_PRIVATE_CLASS(html::mixins, html_hyperlink_element_utils) : virtual dom_object_private
{
    std::unique_ptr<url::detail::url_t> url;
    ext::string href;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_HYPERLINK_ELEMENT_UTILS_PRIVATE_HPP
