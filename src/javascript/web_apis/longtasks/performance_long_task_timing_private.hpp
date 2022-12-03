#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONG_TASK_TIMING_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONG_TASK_TIMING_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "performance_timeline/performance_entry_private.hpp"

#include "ext/vector.hpp"
namespace longtasks {class task_attribution_timing;}


DEFINE_PRIVATE_CLASS(longtasks, performance_long_task_timing) : performance_timeline::performance_entry_private
{
    ext::vector<task_attribution_timing*> attribution;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONG_TASK_TIMING_PRIVATE_HPP
