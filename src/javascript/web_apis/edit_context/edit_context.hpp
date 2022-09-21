#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP

#include "dom/nodes/event_target.hpp"
namespace edit_context {class edit_context;}

#include "ext/boolean.hpp"
#include "ext/type_traits.hpp"
#include INCLUDE_INNER_TYPES(edit_context)
namespace dom::nodes {class element;}
namespace css::geometry {class dom_rect;}


class edit_context::edit_context
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(edit_context);
    edit_context() = default;
    edit_context(detail::edit_context_init_t&& options = {});

public js_methods:
    auto update_text(ext::number<ulong> range_start, ext::number<ulong> range_end, ext::string&& new_text) -> void;
    auto update_selection(ext::number<ulong> start, ext::number<ulong> end) -> void;
    auto update_control_bound(css::geometry::dom_rect* new_control_bound) -> void;
    auto update_selection_bound(css::geometry::dom_rect* new_selection_bound) -> void;
    auto update_character_bounds(ext::number<ulong> range_start, const ext::vector<css::geometry::dom_rect*>& character_bounds) -> void;
    auto attached_element() -> ext::vector<dom::nodes::element*>;
    auto character_bounds() -> ext::vector<css::geometry::dom_rect*>;

public js_properties:
    ext::property<ext::string> text;
    ext::property<ext::number<ulong>> selection_start;
    ext::property<ext::number<ulong>> selection_end;
    ext::property<ext::number<ulong>> selection_composition_range_start;
    ext::property<ext::number<ulong>> selection_composition_range_end;
    ext::property<ext::number<ulong>> character_bounds_range_start;
    ext::property<ext::boolean> is_in_composition;
    ext::property<std::unique_ptr<css::geometry::dom_rect>> control_bound;
    ext::property<std::unique_ptr<css::geometry::dom_rect>> selection_bound;

private cpp_properties:
    ext::boolean m_activated;
    ext::vector<css::geometry::dom_rect*> m_cached_character_bounds;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP
