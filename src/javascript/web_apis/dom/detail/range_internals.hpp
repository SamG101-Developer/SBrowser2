#ifndef SBROWSER2_RANGE_INTERNALS_HPP
#define SBROWSER2_RANGE_INTERNALS_HPP

#include <ext/number.hpp>
#include <ext/vector.hpp>
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class node;}
namespace dom::node_ranges {class range;}

namespace dom::detail::range_internals
{
    enum boundary_point_comparison_position {EQUALS = -1, BEFORE = 0, AFTER = 1};

    // containment and position checks
    auto contains(
            nodes::node* new_container,
            node_ranges::range* range)
            -> ext::boolean;

    auto partially_contains(
            nodes::node* new_container,
            node_ranges::range* range)
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
    auto get_range_helpers_variables(
            node_ranges::range* range,
            nodes::node* start_container,
            nodes::node* end_container)
            -> std::tuple<nodes::node*, nodes::node*, ext::vector<nodes::node*>>;

    auto check_parent_exists(
            nodes::node* node)
            -> nodes::node*;

    auto is_textual_based_range_container(
            nodes::node* node)
            -> bool;

    auto clone_character_data_and_append(
            nodes::node* node,
            nodes::document_fragment* fragment,
            ext::number_view<ulong> start_offset,
            ext::number_view<ulong> end_offset,
            ext::boolean_view replace)
            -> nodes::document_fragment*;

    auto append_to_sub_fragment(
            nodes::node* node,
            nodes::document_fragment* fragment,
            nodes::node* start_container,
            nodes::node* end_container,
            ext::number_view<ulong> start_offset,
            ext::number_view<ulong> end_offset)
            -> nodes::document_fragment*;

    auto create_new_node_and_offset(
            nodes::node* start_container,
            nodes::node* end_container,
            ext::number_view<ulong> start_offset)
            -> std::tuple<nodes::node*, ext::number_view<ulong>>;
}

#endif //SBROWSER2_RANGE_INTERNALS_HPP
