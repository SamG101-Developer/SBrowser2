module;
#include "ext/macros/macros.hpp"


export module apis.event_timing.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(event_timing)
{
    class performance_event_timing;
    class event_counts;
    class interaction_counts;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(event_timing)
{
    using performance_observer_init_t = ext::map<ext::string, ext::any>;
}
