#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_data_element) : html::elements::html_element_private
{
    ext::string value;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_ELEMENT_PRIVATE_HPP
