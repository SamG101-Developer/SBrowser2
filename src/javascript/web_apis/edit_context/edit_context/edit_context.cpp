module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.edit_context.edit_context;
import apis.edit_context.edit_context_private;

import apis.css.geometry.dom_rect;
import apis.dom.event_target;

import ext.core;
import js.env.module_type;


auto edit_context::edit_context::update_text(
        ext::number<ulong> range_start,
        ext::number<ulong> range_end,
        ext::string&& new_text)
        -> void
{
    ACCESS_PIMPL;
    return_if (!d->activated);
    d->text.replace(*range_start, *range_end - range_start, std::move(new_text));
}


auto edit_context::edit_context::update_selection(
        ext::number<ulong> start,
        ext::number<ulong> end)
        -> void
{
    // To update a selection with a new 'start' and 'end', set the private 'selection_start' and 'selection_end'
    // attributes to the 'start' and 'end'. Only do this operation if the selection is active, and 'start' is less than
    // 'end'.
    ACCESS_PIMPL;
    return_if (!d->activated || start > end);
    ext::tie(d->selection_start, d->selection_end) = ext::make_tuple(start, end);
}


auto edit_context::edit_context::update_control_bound(
        std::unique_ptr<css::geometry::dom_rect> new_control_bound)
        -> void
{
    // To update the control bound with a 'new_control_bound', set the private 'control_bound' to 'new_control_band'.
    // Only do this operation if the selection is active. This allows for a nullptr to be set as the
    // 'new_control_bound'.
    ACCESS_PIMPL;
    return_if (!d->activated);
    d->control_bound = std::move(new_control_bound);
}


auto edit_context::edit_context::update_selection_bound(
        std::unique_ptr<css::geometry::dom_rect> new_selection_bound)
        -> void
{
    // To update the selection bound with a 'new_selection_bound', set the private 'selection_bound' to
    // 'new_selection_band'. Only do this operation if the selection is active. This allows for a nullptr to be set as
    // the 'new_selection_bound'.
    ACCESS_PIMPL;
    return_if (!d->activated);
    d->selection_bound = std::move(new_selection_bound);
}


auto edit_context::edit_context::update_character_bounds(
        ext::number<ulong> range_start,
        ext::vector<std::unique_ptr<css::geometry::dom_rect>>&& character_bounds)
        -> void
{
    // To update the character bounds with a new 'range_start' and 'character_bounds', set the private
    // 'character_bounds_range_start' and 'cached_character_bounds' to 'range_start' and 'character_bounds'.
    ACCESS_PIMPL;
    return_if (!d->activated);
    d->character_bounds_range_start = range_start;
    d->cached_character_bounds = std::move(character_bounds);
}


auto edit_context::edit_context::character_bounds()
        -> ext::vector_span<css::geometry::dom_rect*>
{
    // To view the character_bounds, the private 'cached_character_bounds' are viewed to get their underlying pointers,
    // and returned as a view over a vector.
    ACCESS_PIMPL;
    return_if (!d->activated) {};
    return {d->cached_character_bounds | ranges::views::underlying};
}


auto edit_context::edit_context::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .ctor<edit_context_init_t&&>()
        .function("updateText", &edit_context::update_text)
        .function("updateSelection", &edit_context::update_selection)
        .function("updateControlBound", &edit_context::update_control_bound)
        .function("updateSelectionBound", &edit_context::update_selection_bound)
        .function("updateSelectionBound", &edit_context::update_character_bounds)
        .function("attachedElements", &edit_context::attached_elements)
        .function("characterBounds", &edit_context::character_bounds)
        .property("text", &edit_context::get_text)
        .property("selectionStart", &edit_context::get_selection_start)
        .property("selectionEnd", &edit_context::get_selection_end)
        .property("compositionRangeStart", &edit_context::get_composition_range_start)
        .property("compositionRangeEnd", &edit_context::get_composition_range_end)
        .property("characterBoundsRangeStart", &edit_context::get_character_bounds_range_start)
        .property("isInComposition", &edit_context::get_is_in_composition)
        .property("controlBound", &edit_context::get_control_bound)
        .property("selectionBound", &edit_context::get_selection_bound)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
