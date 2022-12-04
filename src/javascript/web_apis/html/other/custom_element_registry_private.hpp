#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_CUSTOM_ELEMENT_REGISTRY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_CUSTOM_ELEMENT_REGISTRY_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "ext/map.ixx"
#include "ext/promise.ixx"
#include "ext/set.hpp"


DEFINE_PRIVATE_CLASS(html::other, custom_element_registry) : dom_object_private
{
    ext::boolean element_definition_is_running;
    ext::set<std::unique_ptr<dom::detail::custom_element_definition_t>> custom_element_definitions;
    ext::map<ext::string, ext::promise<detail::custom_element_constructor_t>> when_defined_promise_map;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_CUSTOM_ELEMENT_REGISTRY_PRIVATE_HPP
