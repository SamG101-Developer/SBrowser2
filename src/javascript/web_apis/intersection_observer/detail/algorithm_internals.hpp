#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/array.ixx"

#include "ext/expected.ixx"
#include "ext/map.ixx"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(intersection_observer)
#include INCLUDE_INNER_TYPES(hr_time)

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}
namespace intersection_observer {class intersection_observer;}
namespace css::geometry {class dom_rect;}


namespace intersection_observer::detail
{
    auto intersection_root(
            intersection_observer* observer)
            -> dom::nodes::node*;

    auto implicit_root(
            intersection_observer* observer)
            -> dom::nodes::node*;

    auto is_explicit_root_observer(
            intersection_observer* observer)
            -> ext::boolean;

    auto is_implicit_root_observer(
            intersection_observer* observer)
            -> ext::boolean;

    auto content_clip(
            dom::nodes::element* element)
            -> css::geometry::dom_rect;

    auto parse_root_margin(
            ext::string_view margin_string)
            -> ext::expected<ext::array<ext::number<int>, 4>, ext::failure_t>;

    auto queue_intersection_observer_task(
            dom::nodes::document* document)
            -> void;

    auto queue_intersection_observer_entry(
            intersection_observer* observer,
            dom::nodes::document* document,
            const hr_time::dom_high_res_time_stamp& time,
            css::geometry::dom_rect* root_bounds,
            css::geometry::dom_rect* bounding_client_rect,
            css::geometry::dom_rect* intersection_rect,
            ext::boolean intersecting_flag,
            dom::nodes::element* target)
            -> void;

    auto notify_intersection_observers(
            dom::nodes::document* document)
            -> void;

    auto compute_intersection_of_target_element_and_root(
            dom::nodes::element* target_element,
            dom::nodes::element* intersection_root)
            -> css::geometry::dom_rect;

    auto run_update_intersection_observations_steps(
            dom::nodes::document* document,
            ext::string_view time)
            -> void;

    auto pending_initial_intersection_observer_targets(
            dom::nodes::document* document)
            -> ext::boolean;

    auto root_intersection_rectangle(
            intersection_observer* observer)
            -> css::geometry::dom_rect;
}


struct intersection_observer::detail::intersection_observer_registration_t
{
    intersection_observer* observer;
    ext::number<int> previous_threshold_index;
    ext::boolean previous_is_intersecting;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP
