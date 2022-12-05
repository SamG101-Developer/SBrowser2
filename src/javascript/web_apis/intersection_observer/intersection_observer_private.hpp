#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(intersection_observer)
#include "ext/array.ixx"
#include "ext/memory.ixx"
#include "ext/vector.hpp"

namespace css::geometry {class dom_rect_readonly;}


DEFINE_PRIVATE_CLASS(intersection_observer, intersection_observer) : virtual dom_object_private
{
    detail::intersection_observer_callback_t callback;
    ext::array<int, 4> root_margin;
    ext::vector<dom::nodes::element*> observation_targets;
    ext::vector<intersection_observer*> queued_entries;
    ext::vector<ext::number<double>> thresholds;
    std::observer_ptr<dom::nodes::node> root;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER_INTERSECTION_OBSERVER_PRIVATE_HPP
