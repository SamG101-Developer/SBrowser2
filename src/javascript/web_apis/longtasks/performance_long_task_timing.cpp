#include "performance_long_task_timing.hpp"

#include "ext/vector.hpp"
#include "ext/span.hpp"


auto longtasks::performance_long_task_timing::get_attribution() const -> ext::vector_view<task_attribution_timing*>
{
    ACCESS_PIMPL(const performance_long_task_timing);
    return ext::vector_span{d->attribution.begin(), d->attribution.end()};
}
