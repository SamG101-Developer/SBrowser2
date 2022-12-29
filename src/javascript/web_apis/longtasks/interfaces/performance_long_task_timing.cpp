module;
#include "ext/macros/macros.hpp"


module apis.longtasks.performance_long_task_timing;
import apis.longtasks.types;

import ext.core;


auto longtasks::performance_long_task_timing::get_attribution() const -> ext::span<task_attribution_timing*>
{
    ACCESS_PIMPL;
    return d->attribution;
}
