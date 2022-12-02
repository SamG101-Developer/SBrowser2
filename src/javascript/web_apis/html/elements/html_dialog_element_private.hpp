#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include "ext/memory.ixx"


DEFINE_PRIVATE_CLASS(html::elements, html_dialog_element) : html::elements::html_element_private
{
    ext::boolean open;
    ext::string return_value;

    ext::boolean is_modal_flag;
    std::observer_ptr<html_element> previously_focused_element;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DIALOG_ELEMENT_PRIVATE_HPP
