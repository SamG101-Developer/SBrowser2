#include "performance_measure.hpp"
#include "performance_measure_private.hpp"

#include "hr_time/detail/time_internals.hpp"


user_timing::performance_measure::performance_measure()
{
    INIT_PIMPL(performance_measure);
    ACCESS_PIMPL(performance_measure);

    auto e = js::env::env::current();
    d->entry_type = u"measure";
    d->start_time = hr_time::detail::current_hr_time(e.js.global());

    // TODO : name, duration, (start_time?)
}


auto user_timing::performance_measure::get_detail() const -> ext::any
{
    ACCESS_PIMPL(const performance_measure);
    return d->detail;
}
