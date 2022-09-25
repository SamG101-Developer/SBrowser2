#include "interaction_counts.hpp"


event_timing::interaction_counts::interaction_counts()
{
    INIT_PIMPL(interaction_counts);
}


auto event_timing::interaction_counts::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<interaction_counts>{isolate}
        .inherit<dom_object>()
        .inherit<ext::map_like_linked<ext::string, ext::number<ulonglong>>>()
        .auto_wrap_objects();

    return std::move(conversion);
}
