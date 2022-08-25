#include "performance_paint_timing.hpp"

#include "performance_timeline/performance_entry.hpp"


paint_timing::performance_paint_timing::performance_paint_timing()
{
    bind_get(name);
    bind_get(entry_type);
    bind_get(start_time);
    bind_get(duration);
}


auto paint_timing::performance_paint_timing::get_name()
        const -> decltype(this->name)::value_t
{
    return "first-paint";
}


auto paint_timing::performance_paint_timing::get_entry_type()
        const -> decltype(this->entry_type)::value_t
{
    return "paint";
}


auto paint_timing::performance_paint_timing::get_start_time()
        const -> decltype(this->start_time)::value_t
{
    // TODO
}


auto paint_timing::performance_paint_timing::get_duration()
        const -> decltype(this->duration)::value_t
{
    return 0.0;
}


auto paint_timing::performance_paint_timing::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<performance_paint_timing>{isolate}
        .inherit<performance_timeline::performance_entry>()
        .auto_wrap_objects();
}
