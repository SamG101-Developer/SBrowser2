module;
#include "ext/macros.hpp"


export module apis.longtasks.performance_long_task_timing:p;
import apis.performance_timeline.performance_entry;

IMPORT_ALL_TYPES(longtasks);


DEFINE_PRIVATE_CLASS(longtasks, performance_long_task_timing)
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(performance_long_task_timing);

public:
    ext::vector<task_attribution_timing*> attribution;
};
