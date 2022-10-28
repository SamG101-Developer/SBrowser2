#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LI_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LI_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include "ext/number.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_li_element) : html::elements::html_element_private
{
    ext::number<long> value;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LI_ELEMENT_PRIVATE_HPP
