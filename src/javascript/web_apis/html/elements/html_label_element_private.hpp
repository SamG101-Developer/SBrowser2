#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include "ext/memory.hpp"
#include "ext/string.hpp"
namespace html::elements {class html_element;}
namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::elements, html_label_element) : html::elements::html_element_private
{
    ext::string for_;

    std::observer_ptr<html_element> labeled_control;
    std::observer_ptr<html_form_element> form_owner;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_PRIVATE_HPP
