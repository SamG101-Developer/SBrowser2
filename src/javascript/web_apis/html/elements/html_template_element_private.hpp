#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

namespace dom::nodes {class document_fragment;}


DEFINE_PRIVATE_CLASS(html::elements, html_template_element) : html::elements::html_element_private
{
    std::unique_ptr<dom::nodes::document_fragment> template_contents;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_PRIVATE_HPP
