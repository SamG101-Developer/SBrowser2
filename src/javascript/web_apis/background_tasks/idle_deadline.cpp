#include "idle_deadline.hpp"
#include "idle_deadline_private.hpp"

#include "javascript/environment/realms.hpp"

#include "hr_time/detail/time_internals.hpp"


background_tasks::idle_deadline::idle_deadline()
{
    INIT_PIMPL(idle_deadline);
}


auto background_tasks::idle_deadline::time_remaining() -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(idle_deadline);
    auto e = js::env::env::current();

    // Return the difference between the deadline and current time (the time until the deadline is met). If the
    // difference is negative (the deadline has already been met), then return 0.
    auto now = hr_time::detail::current_hr_time(e.js.global());
    auto deadline = d->get_deadline_time();
    return ext::max(deadline - now, 0.0);
}


auto background_tasks::idle_deadline::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<idle_deadline>{isolate}
        .inherit<dom_object>()
        .function("timeRemaining", &idle_deadline::time_remaining)
        .property("didTimeout", &idle_deadline::get_did_timeout)
        .auto_wrap_objects();

    return std::move(conversion);
}
