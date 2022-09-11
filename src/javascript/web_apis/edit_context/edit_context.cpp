#include "edit_context.hpp"


auto edit_context::edit_context::update_text(
        ext::number<ulong> range_start,
        ext::number<ulong> range_end,
        ext::string&& new_text)
        -> void
{
    return_if (!m_activated);
    text().replace(*range_start, *range_end - range_start, std::move(new_text));
}


auto edit_context::edit_context::update_selection(
        ext::number<ulong> start,
        ext::number<ulong> end)
        -> void
{
    return_if (!m_activated || start > end);
    ext::tie(selection_start, selection_end) = ext::make_tuple(start, end);
}


auto edit_context::edit_context::update_control_bound(
        css::geometry::dom_rect* new_control_bound)
        -> void
{
    return_if (!m_activated);
    control_bound = new_control_bound;
}


auto edit_context::edit_context::update_selection_bound(
        css::geometry::dom_rect* new_selection_bound)
        -> void
{
    return_if (!m_activated);
    selection_bound = new_selection_bound;
}


auto edit_context::edit_context::update_character_bounds(
        ext::number<ulong> range_start,
        const ext::vector<css::geometry::dom_rect*>& character_bounds)
        -> void
{
    return_if (!m_activated);
    character_bounds_range_start = range_start;
    m_cached_character_bounds = character_bounds;
}


auto edit_context::edit_context::character_bounds()
        -> ext::vector<css::geometry::dom_rect*>
{
    return_if (!m_activated) {};
    return m_cached_character_bounds;
}
