#include "abstract_track.hpp"
#include "dom_object.hpp"

#include <v8pp/class.hpp>


auto html::basic_media::abstract_track::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<abstract_track>{isolate}
        .inherit<dom_object>()
        .var("id", &abstract_track::id, true)
        .var("kind", &abstract_track::kind, true)
        .var("label", &abstract_track::label, true)
        .var("language", &abstract_track::language, true)
        .auto_wrap_objects();
}
