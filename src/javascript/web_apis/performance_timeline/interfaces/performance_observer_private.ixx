module;
#include "ext/macros.hpp"


export module apis.performance_timeline.performance_observer:p;
import apis.dom_object;

IMPORT_ALL_TYPES(performance_timeline);


DEFINE_PRIVATE_CLASS(performance_timeline, performance_observer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(performance_observer);

public:
    detail::performance_observer_callback_t observer_callback;
    ext::vector<std::shared_ptr<performance_entry>> observer_buffer;
    detail::performance_observer_type_t observer_type = detail::performance_observer_type_t::UNDEFINED;
    ext::boolean requires_dropped_entries = false;
};
