#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"
namespace dom::nodes {class element;}
namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::other, element_internals) : dom_object_private
{
    std::observer_ptr<dom::nodes::element> target_element;
    std::observer_ptr<elements::html_form_element> form_owner;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_PRIVATE_HPP
