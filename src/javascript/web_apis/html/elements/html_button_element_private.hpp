#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include "ext/memory.hpp"
namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::elements, html_button_element) : html::elements::html_element_private
{
    ext::boolean disabled;
    std::observer_ptr<html_form_element> form;

    ext::string form_action;
    ext::string form_enctype;
    ext::string form_method;
    ext::boolean form_no_validate;

    ext::string name;
    detail::button_state_t type;
    ext::string value;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_PRIVATE_HPP
