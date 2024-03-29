module;
#include "ext/macros.hpp"


module apis.performance_timeline.performance_entry;
import apis.hr_time.types;

import ext.core;
import js.env.module_type;


performance_timeline::performance_entry::performance_entry()
{
    INIT_PIMPL;
}


auto performance_timeline::performance_entry::get_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->name;
}


auto performance_timeline::performance_entry::get_entry_type() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->entry_type;
}


auto performance_timeline::performance_entry::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->start_time;
}


auto performance_timeline::performance_entry::get_duration() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->duration;
}


auto performance_timeline::performance_entry::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("name", &performance_entry::get_name)
        .property("entryType", &performance_entry::get_entry_type)
        .property("startTime", &performance_entry::get_start_time)
        .property("duration", &performance_entry::get_duration)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
