module;
#include "ext/macros/pimpl.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.performance_timeline.performance_entry;
import apis.hr_time.types;

import ext.string;
import ext.tuple;


performance_timeline::performance_entry::performance_entry()
{
    INIT_PIMPL;
}


auto performance_timeline::performance_entry::get_name() const -> ext::string
{
    ACCESS_PIMPL;
    return d->name;
}


auto performance_timeline::performance_entry::get_entry_type() const -> ext::string
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


auto performance_timeline::performance_entry::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<this_t>
{
    decltype(auto) conversion = v8pp::class_<performance_entry>{isolate}
        .inherit<dom_object>()
        .property("name", &performance_entry::get_name)
        .property("entryType", &performance_entry::get_entry_type)
        .property("startTime", &performance_entry::get_start_time)
        .property("duration", &performance_entry::get_duration)
        .auto_wrap_objects();

    return std::move(conversion);
}
