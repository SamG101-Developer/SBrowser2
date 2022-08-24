#include "idle_deadline.hpp"

#include "high_resolution_time/performance.hpp"


auto background_tasks::idle_deadline::time_remaining()
        -> high_resolution_time::detail::dom_high_res_time_stamp_t
{
    // Return the difference between the deadline and current time (the time until the deadline is met). If the
    // difference is negative (the deadline has already been met), then return 0.
    auto now = high_resolution_time::performance{}.now();
    auto deadline = m_get_deadline_time();
    return ext::max(deadline - now, 0);
}
