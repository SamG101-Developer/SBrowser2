#include "audio_track.hpp"

#include "html/basic_media/abstract_track.hpp"


auto html::basic_media::audio_track::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<audio_track>{isolate}
        .inherit<abstract_track>()
        .var("enabled", &audio_track::enabled, false)
        .var("sourceBuffer", &audio_track::source_buffer, true)
        .auto_wrap_objects();
}
