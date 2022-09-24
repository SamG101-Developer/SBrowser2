#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(performance_timeline)


DEFINE_PRIVATE_CLASS(performance_timeline, performance_observer) : dom_object_private
{
    detail::performance_observer_callback_t observer_callback;
    detail::performance_entry_list_t observer_buffer;
    detail::performance_observer_type_t observer_type = detail::performance_observer_type_t::UNDEFINED;
    ext::boolean requires_dropped_entries = false;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_OBSERVER_PRIVATE_HPP
