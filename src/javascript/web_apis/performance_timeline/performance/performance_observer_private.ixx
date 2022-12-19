module;
#include "ext/macros/pimpl.hpp"


export module apis.performance_timeline.performance_observer_private;
import apis._.dom_object_private;
import apis.performance_timeline.types;

import ext.boolean;


DEFINE_PRIVATE_CLASS(performance_timeline, performance_observer)
        : virtual dom_object_private
{
    detail::performance_observer_callback_t observer_callback;
    detail::performance_entry_list_t observer_buffer;
    detail::performance_observer_type_t observer_type = detail::performance_observer_type_t::UNDEFINED;
    ext::boolean requires_dropped_entries = false;
};
