#ifndef SBROWSER2_RANGE_INTERNALS_HPP
#define SBROWSER2_RANGE_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/tuple.hpp"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class character_data;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class node;}
namespace dom::node_ranges {class range;}

namespace dom::detail::range_internals
{
    enum boundary_point_comparison_position : short {EQUALS = -1, BEFORE = 0, AFTER = 1};
    enum append_action {EXTRACT, CLONE};

    // containment and position checks
    auto contains(
            nodes::node* new_container,
            const node_ranges::range* range)
            -> ext::boolean;

    auto partially_contains(
            nodes::node* new_container,
            const node_ranges::range* range)
            -> ext::boolean;

    auto set_start_or_end(
            node_ranges::range* range,
            nodes::node* new_container,
            ext::number_view<ulong> new_offset,
            ext::boolean_view start)
            -> void;

    auto position_relative(
            nodes::node* start_container,
            ext::number_view<ulong> start_offset,
            nodes::node* end_container,
            ext::number_view<ulong> end_offset)
            -> boundary_point_comparison_position;

    // other general helper methods for ranges
    auto get_range_containment_children(
            node_ranges::range* range,
            nodes::node* start_container,
            nodes::node* end_container)
            -> ext::tuple<nodes::node*, nodes::node*, ranges::any_view<nodes::node*>>;

    auto copy_data(
            nodes::node* child,
            nodes::document_fragment* fragment,
            nodes::character_data* container,
            ext::number_view<ulong> start_offset,
            ext::number_view<ulong> end_offset,
            ext::boolean_view replace)
            -> nodes::document_fragment*;

    auto append_to_sub_fragment(
            nodes::node* child,
            nodes::document_fragment* fragment,
            nodes::node* start_container,
            ext::number_view<ulong> start_offset,
            nodes::node* end_container,
            ext::number_view<ulong> end_offset,
            append_action what)
            -> nodes::document_fragment*;

    auto create_new_node_and_offset(
            nodes::node* start_container,
            nodes::node* end_container,
            ext::number_view<ulong> start_offset)
            -> ext::tuple<nodes::node*, ext::number<ulong>>;
}

#endif //SBROWSER2_RANGE_INTERNALS_HPP
