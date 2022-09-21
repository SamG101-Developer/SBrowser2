#include "idle_deadline.hpp"

#include "javascript/environment/realms_2.hpp"

#include "background_tasks/detail/processing_internals.hpp"
#include "hr_time/detail/time_internals.hpp"


background_tasks::idle_deadline::idle_deadline()
        : INIT_PIMPL
{}


auto background_tasks::idle_deadline::time_remaining()
        -> hr_time::dom_high_res_time_stamp
{
    // Return the difference between the deadline and current time (the time until the deadline is met). If the
    // difference is negative (the deadline has already been met), then return 0.
    JS_REALM_GET_CURRENT;
    auto now = hr_time::detail::current_hr_time(current_global_object);
    auto deadline = d_ptr->get_deadline_time();
    return ext::max(deadline - now, 0);
}


auto background_tasks::idle_deadline::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<idle_deadline>{isolate}
        .inherit<dom_object>()
        .function("timeRemaining", &idle_deadline::time_remaining)
        .var("didTimeout", &idle_deadline::did_timeout, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
