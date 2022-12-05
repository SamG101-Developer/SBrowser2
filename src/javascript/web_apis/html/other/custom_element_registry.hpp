#ifndef SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP
#define SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP


namespace html::other {class custom_element_registry;}
namespace html::other {class custom_element_registry_private;}



#include "ext/optional.ixx"

#include "ext/set.hpp"
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace html::elements {class html_element;}


class html::other::custom_element_registry
        : public virtual dom_object
{
public constructors:
    custom_element_registry();
    MAKE_PIMPL(custom_element_registry);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto define(ext::string_view name, detail::custom_element_constructor_t&& constructor, detail::element_definition_options_t&& options = {}) -> void;
    auto get(ext::string_view name) -> ext::optional<detail::custom_element_constructor_t>;
    auto when_defined(ext::string_view name) -> ext::promise<detail::custom_element_constructor_t>;
    auto upgrade(dom::nodes::node* root) -> void;
};


#endif //SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP
