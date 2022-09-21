#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SCRIPTING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SCRIPTING_INTERNALS_HPP

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace html::elements {class html_script_element}


namespace html::detail
{
    auto is_scripting_enabled(
            dom::nodes::node* node)
            -> ext::boolean;

    auto is_scripting_disabled(
            dom::nodes::node* node)
            -> ext::boolean;

    auto mark_as_ready(
            detail::script_t* result)
            -> void;

    auto script_element_is_potentially_render_blocking(
            html::elements::html_script_element* element)
            -> ext::boolean;

    auto immediately_prepare_script_element(
            html::elements::html_script_element* element)
            -> void;

    auto prepare_script_element(
            html::elements::html_script_element* element)
            -> void;

    auto execute_script_element(
            html::elements::html_script_element* element)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SCRIPTING_INTERNALS_HPP
