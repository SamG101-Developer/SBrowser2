#include "edit_context.hpp"

#include "css/geometry/dom_rect.hpp"


auto edit_context::edit_context::update_text(
        ext::number<ulong> range_start,
        ext::number<ulong> range_end,
        ext::string&& new_text)
        -> void
{
    ACCESS_PIMPL(edit_context);
    return_if (!d->activated);
    d->text.replace(*range_start, *range_end - range_start, std::move(new_text));
}


auto edit_context::edit_context::update_selection(
        ext::number<ulong> start,
        ext::number<ulong> end)
        -> void
{
    ACCESS_PIMPL(edit_context);
    return_if (!d->activated || start > end);
    ext::tie(d->selection_start, d->selection_end) = ext::make_tuple(start, end);
}


auto edit_context::edit_context::update_control_bound(
        css::geometry::dom_rect* new_control_bound)
        -> void
{
    ACCESS_PIMPL(edit_context);
    return_if (!d->activated);
    d->control_bound.reset(new_control_bound);
}


auto edit_context::edit_context::update_selection_bound(
        css::geometry::dom_rect* new_selection_bound)
        -> void
{
    ACCESS_PIMPL(edit_context);
    return_if (!d->activated);
    d->selection_bound.reset(new_selection_bound);
}


auto edit_context::edit_context::update_character_bounds(
        ext::number<ulong> range_start,
        const ext::vector<css::geometry::dom_rect*>& character_bounds)
        -> void
{
    ACCESS_PIMPL(edit_context);
    return_if (!d->activated);
    d->character_bounds_range_start = range_start;
    d->cached_character_bounds = character_bounds;
}


auto edit_context::edit_context::character_bounds()
        -> ext::vector_view<css::geometry::dom_rect*>
{
    ACCESS_PIMPL(edit_context);
    return_if (!d->activated) {};
    return {d->cached_character_bounds.begin(), d->cached_character_bounds.end()};
}
