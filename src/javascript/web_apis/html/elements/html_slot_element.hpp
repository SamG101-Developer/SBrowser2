#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_slot_element;}

#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}
namespace dom::nodes {class text;}


class html::elements::html_slot_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_slot_element);
    html_slot_element() = default;

public js_methods:
    auto assigned_nodes(detail::assigned_node_options_t&& = {}) const -> ext::vector<dom::nodes::node*>;
    auto assigned_elements(detail::assigned_node_options_t&& = {}) const -> ext::vector<dom::nodes::element*>;
    auto assign(type_is<dom::nodes::element*, dom::nodes::text*> auto*... nodes) -> void;

public js_properties:
    ext::property<ext::string> name;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_HPP
