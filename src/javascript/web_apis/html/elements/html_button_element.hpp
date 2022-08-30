#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_button_element;}

#include USE_INNER_TYPES(html)
namespace html::elements {class html_form_element;}


class html::elements::html_button_element
        : public html_element
        , public mixins::validatable
{
public constructors:
    DOM_CTORS(html_button_element);
    html_button_element();

public js_properties:
    ext::property<html_form_element*> form;
    ext::property<ext::boolean> disabled;
    ext::property<ext::boolean> form_no_validate;
    ext::property<ext::string> form_action;
    ext::property<ext::string> form_enctype;
    ext::property<ext::string> form_method;
    ext::property<ext::string> form_target;
    ext::property<ext::string> name;
    ext::property<detail::button_state_t> type;
    ext::property<ext::string> value;

    ext::property<std::unique_ptr<dom::nodes::node*>> labels;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_HPP
