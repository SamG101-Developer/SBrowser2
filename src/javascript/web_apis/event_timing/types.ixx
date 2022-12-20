module;
#include "ext/macros/pimpl.hpp"


export module apis.event_timing.types;
import ext.any;
import ext.map;
import ext.string;


DEFINE_FWD_DECL_NAMESPACE(event_timing)
{
    class performance_event;
    class event_counts;
    class interaction_counts;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(event_timing)
{
    using performance_observer_init_t = ext::map<ext::string, ext::any>;
}
