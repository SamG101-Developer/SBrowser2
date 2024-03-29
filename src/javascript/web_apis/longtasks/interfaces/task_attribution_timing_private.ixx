module;
#include "ext/macros.hpp"


export module apis.longtasks.task_attribution_timing:p;
import apis.performance_timeline.performance_entry;


DEFINE_PRIVATE_CLASS(longtasks, task_attribution_timing)
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(task_attribution_timing);
};
