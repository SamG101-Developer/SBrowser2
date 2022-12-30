module;
#include "ext/macros.hpp"


export module apis.performance_timeline.performance_observer:p;
import apis.dom_object;
import apis.performance_timeline.types;

import ext.core;


DEFINE_PRIVATE_CLASS(performance_timeline, performance_observer)
        : virtual dom_object_private
{
    detail::performance_observer_callback_t observer_callback;
    ext::vector<std::shared_ptr<performance_entry>> observer_buffer;
    detail::performance_observer_type_t observer_type = detail::performance_observer_type_t::UNDEFINED;
    ext::boolean requires_dropped_entries = false;
};
