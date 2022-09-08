#include "video_track.hpp"

#include "html/basic_media/abstract_track.hpp"


auto html::basic_media::video_track::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<abstract_track>{isolate}
        .inherit<abstract_track>()
        .var("selected", &video_track::selected, true)
        .auto_wrap_objects();
}
