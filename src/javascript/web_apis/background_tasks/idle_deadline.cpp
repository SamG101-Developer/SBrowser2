#include "idle_deadline.hpp"

#include "javascript/environment/realms_2.hpp"

#include "hr_time/detail/time_internals.hpp"


auto background_tasks::idle_deadline::time_remaining()
        -> hr_time::dom_high_res_time_stamp
{
    // Return the difference between the deadline and current time (the time until the deadline is met). If the
    // difference is negative (the deadline has already been met), then return 0.
    JS_REALM_GET_CURRENT;
    auto now = hr_time::detail::current_hr_time(current_global_object);
    auto deadline = m_get_deadline_time();
    return ext::max(deadline - now, 0);
}
