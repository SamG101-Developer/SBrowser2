#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(intersection_observer)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace intersection_observers {class intersection_observer;}


namespace intersection_observers::detail::algorithm_internals
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
            -> geometry::dom_rect;

    auto run_update_intersection_observations_steps(
            dom::nodes::document* document,
            ext::string_view time)
            -> void;

    auto pending_initial_intersection_observer_targets(
            dom::nodes::document* document)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_DETAIL_ALGORITHM_INTERNALS_HPP
