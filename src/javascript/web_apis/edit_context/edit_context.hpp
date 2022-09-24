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

#include "edit_context/edit_context_private.hpp"


class edit_context::edit_context
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(edit_context);
    edit_context(detail::edit_context_init_t&& options = {});
    MAKE_PIMPL(edit_context);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto update_text(ext::number<ulong> range_start, ext::number<ulong> range_end, ext::string&& new_text) -> void;
    auto update_selection(ext::number<ulong> start, ext::number<ulong> end) -> void;
    auto update_control_bound(css::geometry::dom_rect* new_control_bound) -> void;
    auto update_selection_bound(css::geometry::dom_rect* new_selection_bound) -> void;
    auto update_character_bounds(ext::number<ulong> range_start, const ext::vector<css::geometry::dom_rect*>& character_bounds) -> void;
    auto attached_element() -> ext::vector<dom::nodes::element*>;
    auto character_bounds() -> ext::vector_view<css::geometry::dom_rect*>;

private js_properties:
    DEFINE_GETTER(text, ext::string);
    DEFINE_GETTER(selection_start, ext::number<ulong>);
    DEFINE_GETTER(selection_end, ext::number<ulong>);
    DEFINE_GETTER(selection_composition_range_start, ext::number<ulong>);
    DEFINE_GETTER(selection_composition_range_end, ext::number<ulong>);
    DEFINE_GETTER(character_bounds_range_start, ext::number<ulong>);
    DEFINE_GETTER(is_in_composition, ext::boolean);
    DEFINE_GETTER(control_bound, css::geometry::dom_rect*);
    DEFINE_GETTER(selection_bound, css::geometry::dom_rect*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP
