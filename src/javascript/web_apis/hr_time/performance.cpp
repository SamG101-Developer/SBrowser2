#include "performance.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/nodes/window.hpp"
#include "hr_time/detail/time_internals.hpp"

#include INCLUDE_INNER_TYPES(hr_time)


hr_time::performance::performance()
{
    INIT_PIMPL(performance);
}


auto hr_time::performance::now()
        -> dom_high_res_time_stamp
{
    // the time at 'now()' is the current high resolution time returned from the detail method, with the global object
    // set to the relevant global object of this Performance class
    JS_REALM_GET_RELEVANT(this);
    return detail::current_hr_time(this_relevant_global_object);
}


auto hr_time::performance::get_time_origin() const -> dom_high_res_time_stamp
{
    // the 'time_origin' of this Performance class will always be the value returned from the detail method which gets
    // the value from the global object, set to the relevant global object of the Performance class
    JS_REALM_GET_RELEVANT(this);
    return detail::get_time_origin_timestamp(this_relevant_global_object);
}


auto hr_time::performance::get_event_counts() const -> const event_timing::event_counts*
{
    JS_REALM_GET_RELEVANT(this);
    return v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object)->m_event_counts.get();
}


auto hr_time::performance::get_interaction_counts() const -> const event_timing::interaction_counts*
{
    JS_REALM_GET_RELEVANT(this);
    return v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object)->m_interaction_counts.get();
}


auto hr_time::performance::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversions = v8pp::class_<performance>{isolate}
            .inherit<dom::nodes::event_target>()
            .function("now", &performance::now)
            .property("timeOrigin", &performance::get_time_origin)
            .property("eventCounts", &performance::get_event_counts)
            .property("interactionCounts", &performance::get_interaction_counts)
            .auto_wrap_objects();

    return std::move(conversions);
}
