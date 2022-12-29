module;
#include "ext/macros/pimpl.hpp"


export module apis.longtasks.performance_long_task_timing_private;
import apis.performance_timeline.performance_entry_private;

import apis.longtasks.types;
import ext.core;


DEFINE_PRIVATE_CLASS(longtasks, performance_long_task_timing)
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(performance_long_task_timing);

public:
    ext::vector<task_attribution_timing*> attribution;
};
