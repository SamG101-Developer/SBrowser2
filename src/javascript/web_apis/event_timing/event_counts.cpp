#include "event_counts.hpp"
#include "event_counts_private.hpp"


event_timing::event_counts::event_counts()
{
    INIT_PIMPL(event_counts);
}


auto event_timing::event_counts::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<event_counts>{isolate}
        .inherit<dom_object>()
        .inherit<ext::map_like_linked<ext::string, ext::number<ulonglong>>>()
        .auto_wrap_objects();

    return std::move(conversion);
}
