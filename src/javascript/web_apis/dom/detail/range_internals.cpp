#include "range_internals.hpp"

#include <tuple>

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "dom/nodes/character_data.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/document_type.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/other/dom_implementation.hpp"
#include "dom/ranges/range.hpp"

#include "url/url.hpp"

#include <range/v3/view/filter.hpp>


auto dom::detail::range_internals::contains(
        nodes::node* const new_container,
        const node_ranges::range* const range)
        -> ext::boolean
{
    // get the current length of the new container that is being checked if it is contained in the range
    const auto l = tree_internals::length(new_container);

    return range->m_root == tree_internals::root(new_container)
            && position_relative(new_container, 0, range->start_container(), range->start_offset()) == AFTER
            && position_relative(new_container, l, range->end_container()  , range->end_offset()  ) == BEFORE;
}


auto dom::detail::range_internals::partially_contains(
        nodes::node* const new_container,
        const node_ranges::range* const range)
        -> ext::boolean
{
    return tree_internals::is_ancestor(new_container, range->start_container()) != tree_internals::is_ancestor(new_container, range->end_container());
}


auto dom::detail::range_internals::set_start_or_end(
        node_ranges::range* const range,
        nodes::node* const new_container,
        ext::number_view<ulong> new_offset,
        ext::boolean_view start) -> void
{
    exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [new_container] {return dynamic_cast<nodes::document_type*>(new_container);},
            "The container of a Range can not be a DocumentType node");

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [new_offset, index = tree_internals::index(new_container)] {return new_offset > index;},
            "The offset must be <= the index of the container");

    const auto root_match = range->m_root == tree_internals::root(new_container);

    // set the start of the range to the 'new_container' and 'new_offset'
    if (start)
    {
        // record if the new boundary point is after the range's current end - in other words, if the new start is going
        // to be after the range's end
        const auto new_boundary_point_after_current_end = position_relative(new_container, new_offset, range->end_container(), range->end_offset()) == AFTER;

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
        const auto new_boundary_point_before_current_start = position_relative(new_container, new_offset, range->start_container(), range->start_offset()) == BEFORE;

        // if the new end is going to be after the range's start, then update the range's start to be the new end,
        // otherwise keep it the same; update the range's end to the new end (range could end up empty if the start and
        // end are the same)
        range->start_container = root_match || new_boundary_point_before_current_start ? new_container : range->start_container();
        range->start_offset    = root_match || new_boundary_point_before_current_start ? new_offset : range->start_offset();
        range->end_container   = new_container;
        range->end_offset      = new_offset;
    }
}


auto dom::detail::range_internals::get_range_containment_children(
        node_ranges::range* range,
        nodes::node* const start_container,
        nodes::node* const end_container)
        -> ext::tuple<nodes::node*, nodes::node*, ranges::any_view<nodes::node*>>
{
    const auto common_ancestor_children = *range->common_ancestor_container->child_nodes();

    auto* first_partially_contained_child = !detail::tree_internals::is_ancestor(start_container, end_container)
            ? ranges::first_where(common_ancestor_children, ext::bind_back(detail::range_internals::partially_contains, static_cast<node_ranges::range*&&>(range)))
            : nullptr;

    auto* last_partially_contained_child = !detail::tree_internals::is_ancestor(end_container, start_container)
            ? ranges::last_where(common_ancestor_children, ext::bind_back(detail::range_internals::partially_contains, static_cast<node_ranges::range*&&>(range)))
            : nullptr;

    auto contained_children = common_ancestor_children
            | ranges::views::filter(ext::bind_back(detail::range_internals::contains, static_cast<node_ranges::range*&&>(range)));

    return std::make_tuple(first_partially_contained_child, last_partially_contained_child, contained_children);
}


auto dom::detail::range_internals::copy_data(
        nodes::node* const child,
        nodes::document_fragment* const fragment,
        nodes::character_data* const container,
        ext::number_view<ulong> start_offset,
        ext::number_view<ulong> end_offset,
        ext::boolean_view replace)
        -> nodes::document_fragment*
{
    auto* const clone = dynamic_cast<nodes::character_data*>(child->clone_node());
    clone->data = detail::text_internals::substring_data(container, start_offset, end_offset - start_offset);
    detail::mutation_internals::append(clone, fragment);

    if (replace)
        detail::text_internals::replace_data(container, start_offset, end_offset - start_offset, "");
}


auto dom::detail::range_internals::append_to_sub_fragment(
        nodes::node* const child,
        nodes::document_fragment* const fragment,
        nodes::node* const start_container,
        ext::number_view<ulong> start_offset,
        nodes::node* const end_container,
        ext::number_view<ulong> end_offset,
        const append_action what)
        -> nodes::document_fragment*
{
    return_if (!child) nullptr;

    auto* const clone = child->clone_node();
    detail::mutation_internals::append(clone, fragment);
    node_ranges::range subrange;
    subrange.start_container = start_container;
    subrange.start_offset = start_offset;
    subrange.end_container = end_container;
    subrange.end_offset = end_offset;
    auto* const subfragment = what == EXTRACT ? subrange.extract_contents() : subrange.clone_contents();
    detail::mutation_internals::append(clone, subfragment);
    return subfragment;
}


auto dom::detail::range_internals::create_new_node_and_offset(
        nodes::node* const start_container,
        nodes::node* const end_container,
        ext::number_view<ulong> start_offset)
        -> ext::tuple<nodes::node*, ext::number<ulong>>
{
    auto* const common_ancestor = detail::tree_internals::common_ancestor(start_container, end_container);

    auto* new_node = detail::tree_internals::is_ancestor(start_container, end_container)
            ? start_container
            : common_ancestor->parent_node();

    auto new_offset = detail::tree_internals::is_ancestor(start_container, end_container)
            ? start_offset
            : detail::tree_internals::index(common_ancestor) + 1;

    return tuplet::make_tuple(new_node, new_offset);
}
