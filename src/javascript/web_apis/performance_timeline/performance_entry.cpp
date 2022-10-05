#include "performance_entry.hpp"
#include "performance_entry_private.hpp"


performance_timeline::performance_entry::performance_entry()
{
    INIT_PIMPL(performance_entry);
}


auto performance_timeline::performance_entry::get_name() const -> ext::string
{
    ACCESS_PIMPL(const performance_entry);
    return d->name;
}


auto performance_timeline::performance_entry::get_entry_type() const -> ext::string
{
    ACCESS_PIMPL(const performance_entry);
    return d->entry_type;
}


auto performance_timeline::performance_entry::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_entry);
    return d->start_time;
}


auto performance_timeline::performance_entry::get_duration() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_entry);
    return d->duration;
}


auto performance_timeline::performance_entry::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
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
