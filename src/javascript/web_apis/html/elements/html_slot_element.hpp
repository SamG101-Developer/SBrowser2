#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_slot_element;}
namespace html::elements {class html_slot_element_private;}

#include INCLUDE_INNER_TYPES(html)
#include "ext/ranges.hpp"
namespace dom::mixins {class slottable;}
namespace dom::nodes {class node;}


class html::elements::html_slot_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_slot_element);
    MAKE_PIMPL(html_slot_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto assigned_nodes(detail::assigned_node_options_t&& options = {}) const -> ranges::any_helpful_view<dom::nodes::node*>;
    auto assigned_elements(detail::assigned_node_options_t&& options = {}) const -> ranges::any_helpful_view<dom::nodes::element*>;
    auto assign(ext::type_is<dom::mixins::slottable*> auto*... nodes) -> void;

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_SETTER(name, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SLOT_ELEMENT_HPP
