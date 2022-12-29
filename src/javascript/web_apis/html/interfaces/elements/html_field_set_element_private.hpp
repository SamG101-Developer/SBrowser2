#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"
#include "html/mixins/validatable_private.hpp"

#include "ext/memory.ixx"
namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::elements, html_field_set_element)
        : html::elements::html_element_private
        , html::mixins::validatable_private
{
    ext::boolean disabled;
    std::observer_ptr<html_form_element> form_owner;
    ext::string name;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_PRIVATE_HPP
