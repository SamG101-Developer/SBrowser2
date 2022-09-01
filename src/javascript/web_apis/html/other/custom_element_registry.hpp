#ifndef SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP
#define SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP

#include "dom_object.hpp"
namespace html::other {class custom_element_registry;}

#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
#include "ext/set.hpp"
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace html::elements {class html_element;}


class html::other::custom_element_registry
        : public virtual dom_object
{
public js_methods:
    auto define(ext::string_view name, detail::custom_element_constructor_t&& cosntructor, detail::element_definition_options_t&& options = {}) -> void;
    auto get(ext::string_view name) -> ext::optional<detail::custom_element_constructor_t>;
    auto when_defined(ext::string_view name) -> ext::promise<detail::custom_element_constructor_t>;
    auto upgrade(dom::nodes::node* root) -> void;

private cpp_properties:
    ext::set<dom::detail::custom_element_definition_t*> m_custom_element_definitions;
    ext::boolean m_element_definition_is_running;
    ext::map<ext::string, ext::promise<detail::custom_element_constructor_t>> m_when_defined_promise_map;
};


#endif //SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP
