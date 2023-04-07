module;
#include "ext/macros.hpp"


module apis.hr_time.performance;
import apis.hr_time.detail;
import apis.hr_time.types;

import apis.dom.event_target;
import apis.dom.window;

import js.env.module_type;
import js.env.realms;


hr_time::performance::performance()
{
    INIT_PIMPL;
}


auto hr_time::performance::now() const -> dom_high_res_time_stamp
{
    // The time at 'now()' is the current high resolution time returned from the detail method, with the global object
    // set to the relevant global object of this Performance class.
    auto e = js::env::env::relevant(this);
    return detail::current_hr_time(e.js.global());
}


auto hr_time::performance::get_time_origin() const -> dom_high_res_time_stamp
{
    // The 'time_origin' of this Performance class will always be the value returned from the detail method which gets
    // the value from the global object, set to the relevant global object of the Performance class.
    auto e = js::env::env::relevant(this);
    return detail::get_time_origin_timestamp(e.js.global());
}


auto hr_time::performance::get_event_counts() const -> event_timing::event_counts*
{
    auto e = js::env::env::relevant(this);
    return e.cpp.global<dom::window*>()->d_func()->event_counts.get();
}


auto hr_time::performance::get_interaction_counts() const -> event_timing::interaction_counts*
{
    auto e = js::env::env::relevant(this);
    return e.cpp.global<dom::window*>()->d_func()->interaction_counts.get();
}


auto hr_time::performance::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .function("now", &performance::now)
        .property("timeOrigin", &performance::get_time_origin)
        .property("eventCounts", &performance::get_event_counts)
        .property("interactionCounts", &performance::get_interaction_counts)
        .auto_wrap_objects();

    V8_INTEROP_EXTEND_JS_OBJECT(WINDOW)
        .property("eventCounts", &performance::get_event_counts)
        .property("interactionCounts", &performance::get_interaction_counts);

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
