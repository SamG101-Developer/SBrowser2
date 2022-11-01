#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::elements, html_output_element) : html::elements::html_element_private
{
    ext::string for_;
    ext::string name;
    std::observer_ptr<html_form_element> form;

    ext::string default_value_override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_PRIVATE_HPP
