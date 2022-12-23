module;
#include "ext/macros/pimpl.hpp"


export module apis.intersection_observer.intersection_observer_private;
import apis.dom_object_private;

import apis.dom.types;
import apis.intersection_observer.types;
import ext.core;


DEFINE_PRIVATE_CLASS(intersection_observer, intersection_observer)
        : virtual dom_object_private
{
    detail::intersection_observer_callback_t callback;
    ext::array<int, 4> root_margin;
    ext::vector<dom::element*> observation_targets;
    ext::vector<intersection_observer*> queued_entries;
    ext::vector<ext::number<double>> thresholds;
    std::observer_ptr<dom::node> root;
};
