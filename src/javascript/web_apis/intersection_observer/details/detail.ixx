module;
#include "ext/macros/pimpl.hpp"


export module apis.intersection_observer.detail;

import apis.dom.types;
import apis.hr_time.types;
import apis.intersection_observer.types;
import apis.css.geoemtry.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(intersection_observer)
{
    /* [3.2.1] */ auto initialize_new_intersection_observer(intersection_observer* observer) -> void;
    /* [3.2.2] */ auto observe_target_element(intersection_observer* observer, dom::element* target) -> void;
    /* [3.2.3] */ auto unobserve_target_element(intersection_observer* observer, dom::element* target) -> void;
    /* [3.2.4] */ auto queue_intersection_observer_task(dom::document* document) -> void;
    /* [3.2.5] */ auto notify_intersection_observers(dom::document* document) -> void;
    /* [3.2.6] */ auto queue_intersection_observer_entry(
            intersection_observer* observer, dom::document* document, hr_time::dom_high_res_time_stamp time,
            css::geometry::dom_rect* root_bounds, css::geometry::dom_rect* bounding_client_rect,
            css::geometry::dom_rect* intersection_rect, ext::boolean intersecting_flag, dom::element* target) -> void;
    /* [3.2.7] */ auto compute_intersection_of_target_element_and_root(dom::element* target, dom::element* root) -> std::unique_ptr<css::geometry::dom_rect>
    /* [3.2.8] */ auto update_intersection_observer(dom::document* document, dom_high_res_time_stamp time)



    auto content_clip(
            dom::nodes::element* element)
            -> css::geometry::dom_rect;

    auto pending_initial_intersection_observer_targets(
            dom::nodes::document* document)
            -> ext::boolean;

    auto root_intersection_rectangle(
            intersection_observer* observer)
            -> css::geometry::dom_rect;
}
