#include "text_track.hpp"

#include "html/basic_media/abstract_track.hpp"

#include <v8pp/class.hpp>


auto html::basic_media::text_track::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<text_track>{isolate}
        .inherit<abstract_track>()
        .var("inBandDispatchType", &text_track::in_band_dispatch_type, true)
        .var("mode", &text_track::mode, true)
        .var("cues", &text_track::cues, true)
        .var("activeCues", &text_track::active_cues, true)
        .var("sourceBuffer", &text_track::source_buffer, true)
        .auto_wrap_objects();
}
