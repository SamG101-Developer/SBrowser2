#include "performance_measure.hpp"
#include "performance_measure_private.hpp"

#include "hr_time/detail/time_internals.hpp"


user_timing::performance_measure::performance_measure()
{
    INIT_PIMPL(performance_measure);
    JS_REALM_GET_CURRENT;

    ACCESS_PIMPL(performance_measure);
    d->entry_type = u8"measure";
    d->start_time = hr_time::detail::current_hr_time(current_global_object);

    // TODO : name, duration, (start_time?)
}


auto user_timing::performance_measure::get_detail() const -> ext::any
{
    ACCESS_PIMPL(const performance_measure);
    return d->detail;
}
