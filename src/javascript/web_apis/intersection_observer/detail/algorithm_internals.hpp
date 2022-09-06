#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/array.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(intersection_observer)

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}
namespace intersection_observer {class intersection_observer;}


namespace intersection_observer::detail
{
    auto queue_intersection_observer_task(
            dom::nodes::document* document)
            -> void;

    auto notify_intersection_observers(
            dom::nodes::document* document)
            -> void;

    auto queue_intersection_observer_entry(
            intersection_observer* observer,
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

    auto parse_root_margin(
            ext::string_view margin_string)
            -> ext::optional<ext::array<int, 4>>;
}


struct intersection_observer::detail::intersection_observer_registration_t
{
    intersection_observer* observer;
    ext::number<int> previous_threshold_index;
    ext::boolean previous_is_intersecting;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP
