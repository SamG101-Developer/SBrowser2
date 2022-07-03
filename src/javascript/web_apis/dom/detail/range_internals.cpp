#include "range_internals.hpp"

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>

#include <web_apis/dom/nodes/document_type.hpp>
#include <web_apis/dom/ranges/range.hpp>


auto dom::detail::range_internals::contains(
        nodes::node* new_container,
        node_ranges::range* range)
        -> ext::boolean
{
    // get the current length of the new container that is being checked if it is contained in the range
    auto l = tree_internals::length(new_container);

    return range->m_root == tree_internals::root(new_container)
            && position_relative(new_container, 0, range->start_container(), range->start_offset()) == AFTER
            && position_relative(new_container, l, range->end_container()  , range->end_offset()  ) == BEFORE;
}


auto dom::detail::range_internals::partially_contains(
        nodes::node* new_container,
        node_ranges::range* range)
        -> ext::boolean
{
    return tree_internals::is_ancestor(new_container, range->start_container()) ^ tree_internals::is_ancestor(new_container, range->end_container());
}


auto dom::detail::range_internals::set_start_or_end(
        node_ranges::range* range,
        nodes::node* new_container,
        ext::number_view<ulong> new_offset,
        ext::boolean_view start) -> void
{
    exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [new_container] {return dynamic_cast<nodes::document_type*>(new_container);},
            "The container of a Range can not be a DocumentType node");

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [new_offset, index = tree_internals::index(new_container)] {return new_offset > index;},
            "The offset must be <= the index of the container");

    auto root_match = range->m_root == tree_internals::root(new_container);

    // set the start of the range to the 'new_container' and 'new_offset'
    if (start)
    {
        // record if the new boundary point is after the range's current end - in other words, if the new start is going
        // to be after the range's end
        auto new_boundary_point_after_current_end = position_relative(new_container, new_offset, range->end_container(), range->end_offset()) == AFTER;

        // if the new start is going to be after the range's end, then update the range's end to be the new start,
        // otherwise keep it the same; update the range's start to the new start (range could end up empty if the start
        // and end are the same)
        range->end_container   = root_match || new_boundary_point_after_current_end ? new_container : range->end_container();
        range->end_offset      = root_match || new_boundary_point_after_current_end ? new_offset : range->end_offset();
        range->start_container = new_container;
        range->start_offset    = new_offset;
    }

    // set the end of the range to the 'new_container' and 'new_offset'
    else
    {
        // record if the new boundary point is before the range's current start - in other words, if the new end is
        // going to be before the range's start
        auto new_boundary_point_before_current_start = position_relative(new_container, new_offset, range->start_container(), range->start_offset()) == BEFORE;

        // if the new end is going to be after the range's start, then update the range's start to be the new end,
        // otherwise keep it the same; update the range's end to the new end (range could end up empty if the start and
        // end are the same)
        range->start_container = root_match || new_boundary_point_before_current_start ? new_container : range->start_container();
        range->start_offset    = root_match || new_boundary_point_before_current_start ? new_offset : range->start_offset();
        range->end_container   = new_container;
        range->end_offset      = new_offset;
    }
}
