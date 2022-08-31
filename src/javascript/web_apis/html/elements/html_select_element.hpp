#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "ext/vector_like.hpp"
namespace html::elements {class html_select_element;}

#include USE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace html::elements {class html_form_element;}


class html::elements::html_select_element
        : public html_element
        , public ext::vector_like_linked<detail::option_like_element_t>
{
public constructors:
    DOM_CTORS(html_select_element);
    html_select_element();

public js_properties:
    ext::property<ext::string> autocomplete;
    ext::property<ext::string> name;
    ext::property<ext::string> type;
    ext::property<ext::string> value;
    ext::property<ext::boolean> disabled;
    ext::property<ext::boolean> multiple;
    ext::property<ext::boolean> required;
    ext::property<html_form_element*> form;
    ext::property<ext::number<ulong>> size;
    ext::property<ext::number<long>> selected_index;

    ext::property<std::unique_ptr<ext::vector<detail::option_like_element_t>>> options;
    ext::property<std::unique_ptr<ext::vector<html_element*>>> selected_options;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>> labels;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_HPP
