module;
#include "ext/macros.hpp"


module apis.background_tasks.idle_deadline;

import apis.hr_time.detail;
import apis.hr_time.types;

import ext.core;

import js.env.module_type;
import js.env.realms;


background_tasks::idle_deadline::idle_deadline()
{
    INIT_PIMPL;
}


auto background_tasks::idle_deadline::time_remaining() -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    auto e = js::env::env::current();

    // Return the difference between the deadline and current time (the time until the deadline is met). If the
    // difference is negative (the deadline has already been met), then return 0.
    auto now = hr_time::detail::current_hr_time(e.js.global());
    auto deadline = d->get_deadline_time();
    return ext::max(deadline - now, 0.0);
}


auto background_tasks::idle_deadline::get_did_timeout() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->timeout;
}


auto background_tasks::idle_deadline::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    decltype(auto) conversion = v8pp::class_<idle_deadline>{isolate}
        .inherit<dom_object>()
        .function("timeRemaining", &idle_deadline::time_remaining)
        .property("didTimeout", &idle_deadline::get_did_timeout)
        .auto_wrap_objects();

    return std::move(conversion);
}
