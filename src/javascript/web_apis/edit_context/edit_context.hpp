#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP


namespace edit_context {class edit_context;}
namespace edit_context {class edit_context_private;}


#include "ext/span.hpp"

#include INCLUDE_INNER_TYPES(edit_context)
namespace dom::nodes {class element;}
namespace css::geometry {class dom_rect;}


class edit_context::edit_context
        : public dom::nodes::event_target
{
public constructors:
    edit_context(detail::edit_context_init_t&& options = {});
    DOM_CTORS(edit_context);
    MAKE_PIMPL(edit_context);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto update_text(ext::number<ulong> range_start, ext::number<ulong> range_end, ext::string&& new_text) -> void;
    auto update_selection(ext::number<ulong> start, ext::number<ulong> end) -> void;
    auto update_control_bound(std::unique_ptr<css::geometry::dom_rect> new_control_bound) -> void;
    auto update_selection_bound(std::unique_ptr<css::geometry::dom_rect> new_selection_bound) -> void;
    auto update_character_bounds(ext::number<ulong> range_start, ext::vector<std::unique_ptr<css::geometry::dom_rect>>&& character_bounds) -> void;
    auto attached_elements() -> ext::vector<dom::nodes::element*>;
    auto character_bounds() -> ext::vector_span<css::geometry::dom_rect*>;

private js_properties:
    DEFINE_GETTER(text, ext::string);
    DEFINE_GETTER(selection_start, ext::number<ulong>);
    DEFINE_GETTER(selection_end, ext::number<ulong>);
    DEFINE_GETTER(composition_range_start, ext::number<ulong>);
    DEFINE_GETTER(composition_range_end, ext::number<ulong>);
    DEFINE_GETTER(character_bounds_range_start, ext::number<ulong>);
    DEFINE_GETTER(is_in_composition, ext::boolean);
    DEFINE_GETTER(control_bound, css::geometry::dom_rect*);
    DEFINE_GETTER(selection_bound, css::geometry::dom_rect*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_HPP
