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

#include <range/v3/view/filter.hpp>


auto dom::detail::is_range_collapsed(
        const node_ranges::abstract_range* range)
        -> ext::boolean
{
    return range->d_func()->start->node == range->d_func()->end->node
            && range->d_func()->start->offset == range->d_func()->end->offset;
}


auto dom::detail::contains(
        nodes::node* const new_container,
        const node_ranges::range* const range)
        -> ext::boolean
{
    // get the current length of the new container that is being checked if it is contained in the range
    const auto l = length(new_container);

    return root(range) == root(new_container)
            && position_relative(new_container, 0, range->d_func()->start->node, range->d_func()->start->offset) == AFTER
            && position_relative(new_container, l, range->d_func()->end->node  , range->d_func()->end->offset  ) == BEFORE;
}


auto dom::detail::partially_contains(
        nodes::node* const new_container,
        const node_ranges::range* const range)
        -> ext::boolean
{
    return is_ancestor(new_container, range->d_func()->start->node) != is_ancestor(new_container, range->d_func()->end->node());
}


auto dom::detail::set_start_or_end(
        node_ranges::range* const range,
        nodes::node* const new_container,
        ext::number<ulong> new_offset,
        ext::boolean  start) -> void
{
    using enum dom::detail::dom_exception_error_t;

    throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [new_container] {return dynamic_cast<nodes::document_type*>(new_container);},
            "The container of a Range can not be a DocumentType node");

    throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [new_offset, index = index(new_container)] {return new_offset > index;},
            "The offset must be <= the index of the container");

    decltype(auto) root_match = root(range) == root(new_container);

    // set the start of the range to the 'new_container' and 'new_offset'
    if (start)
    {
        // record if the new boundary point is after the range's current end - in other words, if the new start is going
        // to be after the range's end
        const auto new_boundary_point_after_current_end = position_relative(new_container, new_offset, range->d_func()->end->node, range->d_func()->end->offset) == AFTER;

        // if the new start is going to be after the range's end, then update the range's end to be the new start,
        // otherwise keep it the same; update the range's start to the new start (range could end up empty if the start
        // and end are the same)
        range->d_func()->end->node     = root_match || new_boundary_point_after_current_end ? new_container : range->d_func()->end->node;
        range->d_func()->end->offset   = root_match || new_boundary_point_after_current_end ? new_offset    : range->d_func()->end->offset;
        range->d_func()->start->node   = new_container;
        range->d_func()->start->offset = new_offset;
    }

    // set the end of the range to the 'new_container' and 'new_offset'
    else
    {
        // record if the new boundary point is before the range's current start - in other words, if the new end is
        // going to be before the range's start
        const auto new_boundary_point_before_current_start = position_relative(new_container, new_offset, range->d_func()->start->node, range->d_func()->start->offset) == BEFORE;

        // if the new end is going to be after the range's start, then update the range's start to be the new end,
        // otherwise keep it the same; update the range's end to the new end (range could end up empty if the start and
        // end are the same)
        range->d_func()->start->node   = root_match || new_boundary_point_before_current_start ? new_container : range->d_func()->start->node;
        range->d_func()->start->offset = root_match || new_boundary_point_before_current_start ? new_offset : range->d_func()->start->offset;
        range->d_func()->end->node     = new_container;
        range->d_func()->end->offset   = new_offset;
    }
}


auto dom::detail::get_range_containment_children(
        node_ranges::range* range,
        nodes::node* const start_container,
        nodes::node* const end_container)
        -> ext::tuple<nodes::node*, nodes::node*, ranges::any_view<nodes::node*>>
{
    decltype(auto) common_ancestor_children = range->d_func()->common_ancestor_container->d_func()->child_nodes();

    auto* first_partially_contained_child = !detail::is_ancestor(start_container, end_container)
            ? *ranges::first_where(common_ancestor_children, BIND_BACK(detail::partially_contains, static_cast<node_ranges::range*&&>(range)))
            : nullptr;

    auto* last_partially_contained_child = !detail::is_ancestor(end_container, start_container)
            ? *ranges::last_where(common_ancestor_children, BIND_BACK(detail::partially_contains, static_cast<node_ranges::range*&&>(range)))
            : nullptr;

    auto contained_children = common_ancestor_children
            | ranges::views::filter(BIND_BACK(detail::contains, static_cast<node_ranges::range*&&>(range)));

    return ext::make_tuple(first_partially_contained_child, last_partially_contained_child, contained_children);
}


auto dom::detail::copy_data(
        nodes::node* const child,
        nodes::document_fragment* const fragment,
        nodes::character_data* const container,
        ext::number<ulong> start_offset,
        ext::number<ulong> end_offset,
        ext::boolean  replace)
        -> nodes::document_fragment*
{
    decltype(auto) clone = std::make_unique<decltype(child)::self_t>(child->clone_node());
    clone->d_func()->data = detail::substring_data(container, start_offset, end_offset - start_offset);
    append(clone, fragment);

    if (replace)
        detail::replace_data(container, start_offset, end_offset - start_offset, "");
}


auto dom::detail::append_to_sub_fragment(
        nodes::node* const child,
        nodes::document_fragment* const fragment,
        nodes::node* const start_container,
        ext::number<ulong> start_offset,
        nodes::node* const end_container,
        ext::number<ulong> end_offset,
        const append_action_t what)
        -> nodes::document_fragment*
{
    return_if (!child) nullptr;

    decltype(auto) clone = std::make_unique<decltype(child)::self_t>(child->clone_node());
    append(clone, fragment);

    node_ranges::range subrange;
    subrange.d_func()->start->node   = start_container;
    subrange.d_func()->start->offset = start_offset;
    subrange.d_func()->end->node     = end_container;
    subrange.d_func()->end->offset   = end_offset;

    auto* const subfragment = what == EXTRACT ? subrange.extract_contents() : subrange.clone_contents();
    append(clone, subfragment);
    return subfragment;
}


auto dom::detail::create_new_node_and_offset(
        nodes::node* const start_container,
        nodes::node* const end_container,
        ext::number<ulong> start_offset)
        -> ext::tuple<nodes::node*, ext::number<ulong>>
{
    auto* const common_ancestor = detail::common_ancestor(start_container, end_container);

    auto* new_node = detail::is_ancestor(start_container, end_container)
            ? start_container
            : common_ancestor->d_func()->parent_node;

    auto new_offset = detail::is_ancestor(start_container, end_container)
            ? start_offset
            : detail::index(common_ancestor) + 1;

    return tuplet::make_tuple(new_node, new_offset);
}
