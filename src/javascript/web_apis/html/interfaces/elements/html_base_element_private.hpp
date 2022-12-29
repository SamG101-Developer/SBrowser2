#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(url)


DEFINE_PRIVATE_CLASS(html::elements, html_base_element) : html::elements::html_element_private
{
    ext::string href;
    ext::string target;

    std::unique_ptr<url::detail::url_t> frozen_base_url; // TODO : needed?
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BASE_ELEMENT_PRIVATE_HPP
