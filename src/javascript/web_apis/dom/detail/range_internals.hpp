#ifndef SBROWSER2_RANGE_INTERNALS_HPP
#define SBROWSER2_RANGE_INTERNALS_HPP

#include "ext/memory.ixx"

#include "ext/tuple.ixx"
#include "ext/type_traits.ixx"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class character_data;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class node;}
namespace dom::node_ranges {class abstract_range;}
namespace dom::node_ranges {class range;}
namespace dom::node_ranges {class static_range;}

namespace dom::detail
{
    auto is_range_collapsed(
            const node_ranges::abstract_range* range)
            -> ext::boolean;

    auto is_Valid(
            const node_ranges::static_range* range)
            -> ext::boolean;

    auto root(
            const node_ranges::range* range)
            -> dom::nodes::node*;

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
            ext::number<ulong> new_offset,
            ext::boolean  start)
            -> void;

    auto position_relative(
            nodes::node* start_container,
            ext::number<ulong> start_offset,
            nodes::node* end_container,
            ext::number<ulong> end_offset)
            -> boundary_point_comparison_position_t;

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
            ext::number<ulong> start_offset,
            ext::number<ulong> end_offset,
            ext::boolean  replace)
            -> nodes::document_fragment*;

    auto append_to_sub_fragment(
            nodes::node* child,
            nodes::document_fragment* fragment,
            nodes::node* start_container,
            ext::number<ulong> start_offset,
            nodes::node* end_container,
            ext::number<ulong> end_offset,
            append_action_t what)
            -> std::unique_ptr<nodes::document_fragment>;

    auto create_new_node_and_offset(
            nodes::node* start_container,
            nodes::node* end_container,
            ext::number<ulong> start_offset)
            -> ext::tuple<nodes::node*, ext::number<ulong>>;
}


struct dom::detail::boundary_point_t
{
    std::observer_ptr<dom::nodes::node> node;
    ext::number<ulong> offset;
};

#endif //SBROWSER2_RANGE_INTERNALS_HPP
