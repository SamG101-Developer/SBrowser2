module;
#include "ext/macros.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <tuplet/tuple.hpp>

module apis.dom.range:p;
import apis.dom.node;
import apis.dom.character_data;
import apis.dom.document_type;
import apis.dom.detail;
import apis.dom.types;

import ext.core;


auto dom::range_private::contains(node* new_container) const -> ext::boolean
{
    // Get the current length of the new container that is being checked if it is contained in the range
    using enum detail::boundary_point_comparison_position_t;
    decltype(auto) l = new_container->d_func()->length();

    return root() == new_container->d_func()->root()
            && position_relative(new_container, 0, start->node.get(), start->offset) == AFTER
            && position_relative(new_container, l, end->node.get()  , end->offset  ) == BEFORE;
}


auto dom::range_private::partially_contains(node* new_container) const -> ext::boolean
{
    return new_container->d_func()->is_ancestor(start->node.get()) != new_container->d_func()->is_ancestor(end->node().get());
}


auto dom::range_private::set_start_or_end(node* new_container, ext::number<ulong> new_offset, ext::boolean at_start) -> void
{
    using enum detail::boundary_point_comparison_position_t;
    using enum detail::dom_exception_error_t;

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return dom_cast<document_type*>(new_container);},
            u8"The container of a Range can not be a DocumentType node");

    detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [new_offset, new_container] {return new_offset > new_container->d_func()->index();},
            u8"The offset must be <= the index of the container");

    auto root_match = root() == new_container->d_func()->root();

    // set the start of the range to the 'new_container' and 'new_offset'
    if (at_start)
    {
        // record if the new boundary point is after the range's current end - in other words, if the new start is going
        // to be after the range's end
        auto new_boundary_point_after_current_end = position_relative(new_container, new_offset, end->node.get(), end->offset) == AFTER;

        // if the new start is going to be after the range's end, then update the range's end to be the new start,
        // otherwise keep it the same; update the range's start to the new start (range could end up empty if the start
        // and end are the same)
        end->node     = root_match || new_boundary_point_after_current_end ? new_container : end->node.get();
        end->offset   = root_match || new_boundary_point_after_current_end ? new_offset    : end->offset;
        start->node   = new_container;
        start->offset = new_offset;
    }

        // set the end of the range to the 'new_container' and 'new_offset'
    else
    {
        // record if the new boundary point is before the range's current start - in other words, if the new end is
        // going to be before the range's start
        auto new_boundary_point_before_current_start = position_relative(new_container, new_offset, start->node.get(), start->offset) == BEFORE;

        // if the new end is going to be after the range's start, then update the range's start to be the new end,
        // otherwise keep it the same; update the range's end to the new end (range could end up empty if the start and
        // end are the same)
        start->node   = root_match || new_boundary_point_before_current_start ? new_container : start->node.get();
        start->offset = root_match || new_boundary_point_before_current_start ? new_offset : start->offset;
        end->node     = new_container;
        end->offset   = new_offset;
    }
}


template <ext::inherit<character_data> T>
auto dom::range_private::copy_data(
        T* child,
        document_fragment* fragment,
        character_data* container,
        ext::number<ulong> start_offset,
        ext::number<ulong> end_offset,
        ext::boolean replace)
        const -> document_fragment*
{
    decltype(auto) clone = child->clone_node();
    clone->d_func()->data = detail::substring_data(container, start_offset, end_offset - start_offset);
    append(clone, fragment);

    if (replace)
        detail::replace_data(container, start_offset, end_offset - start_offset, u"");

    // TODO : return? std::unique_ptr<document_fragment>?
}



auto dom::range_private::get_range_containment_children(
        node* start_container,
        node* end_container)
        const -> ext::tuple<node*, node*, ranges::any_helpful_view<node*>>
{
    ACCESS_QIMPL;
    decltype(auto) common_ancestor_children = common_ancestor_container->d_func()->child_nodes();

    decltype(auto) first_partially_contained_child = !start_container->d_func()->is_ancestor(end_container)
            ? *ranges::first_where(common_ancestor_children, ext::bind_front(partially_contains))
            : nullptr;

    decltype(auto) last_partially_contained_child = !end_container->d_func()->is_ancestor(start_container)
            ? *ranges::last_where(common_ancestor_children, ext::bind_front(partially_contains))
            : nullptr;

    auto contained_children = common_ancestor_children
            | ranges::views::filter(&contains);

    return ext::make_tuple(first_partially_contained_child, last_partially_contained_child, contained_children);
}


auto dom::range_private::append_to_sub_fragment(
        node* const child,
        document_fragment* const fragment,
        node* const start_container,
        ext::number<ulong> start_offset,
        node* const end_container,
        ext::number<ulong> end_offset,
        detail::append_action_t what)
        -> std::unique_ptr<document_fragment>
{
    return_if (!child) nullptr;

    decltype(auto) clone = std::make_unique<decltype(child)::self_t>(child->clone_node());
    append(clone, fragment);

    node_ranges::range subrange;
    subrange.d_func()->start->node   = start_container;
    subrange.d_func()->start->offset = start_offset;
    subrange.d_func()->end->node     = end_container;
    subrange.d_func()->end->offset   = end_offset;

    decltype(auto) subfragment = what == EXTRACT ? subrange.extract_contents() : subrange.clone_contents();
    append(std::move(clone), subfragment);
    return subfragment;
}


auto dom::range_private::create_new_node_and_offset(
        node* const start_container,
        node* const end_container,
        ext::number<ulong> start_offset)
-> ext::tuple<node*, ext::number<ulong>>
{
auto* const common_ancestor = detail::common_ancestor(start_container, end_container);

auto* new_node = detail::is_ancestor(start_container, end_container)
        ? start_container
        : common_ancestor->d_func()->parent_node.get();

auto new_offset = detail::is_ancestor(start_container, end_container)
        ? start_offset
        : detail::index(common_ancestor) + 1;

return tuplet::make_tuple(new_node, new_offset);
}

