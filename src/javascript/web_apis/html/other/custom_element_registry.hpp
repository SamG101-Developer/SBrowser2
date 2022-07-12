#ifndef SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP
#define SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP

#include "dom_object.hpp"
namespace html::other {class custom_element_registry;}

#include "ext/map.hpp"
#include "ext/optional.hpp"
namespace dom::nodes {class node;}
namespace html::elements {class html_element;}


class html::other::custom_element_registry
        : public virtual web_apis::dom_object
{
public aliases:
    using custom_element_constructor = std::function<elements::html_element*()>;

public js_methods:
    auto define(ext::string_view name, custom_element_constructor&& cosntructor, ext::string_any_map_view options = {});
    auto get(ext::string_view name) -> ext::optional<custom_element_constructor>;
    auto when_defined(ext::string_view name) -> std::promise<custom_element_constructor>;
    auto upgrade(dom::nodes::node* root) -> void;
};


#endif //SBROWSER2_CUSTOM_ELEMENT_REGISTRY_HPP
