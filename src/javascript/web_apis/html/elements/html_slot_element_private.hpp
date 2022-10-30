#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include "ext/memory.hpp"
namespace dom::mixins {class slottable;}


DEFINE_PRIVATE_CLASS(html::elements, html_slot_element) : html::elements::html_element_private
{
    ext::string name;

    ext::vector<std::observer_ptr<dom::mixins::slottable>> assigned_nodes;
    ext::vector<std::observer_ptr<dom::mixins::slottable>> manually_assigned_nodes;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_PRIVATE_HPP
