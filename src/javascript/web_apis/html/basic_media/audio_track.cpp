#include "audio_track.hpp"
#include "audio_track_private.hpp"

#include "html/basic_media/abstract_track.hpp"


auto html::basic_media::audio_track::get_enabled() const -> ext::boolean
{
    ACCESS_PIMPL(const audio_track);
    return d->enabled;
}


auto html::basic_media::audio_track::set_enabled(ext::boolean new_enabled) -> ext::boolean
{
    ACCESS_PIMPL(audio_track);
    return d->enabled = new_enabled;
}


auto html::basic_media::audio_track::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<audio_track>{isolate}
        .inherit<abstract_track>()
        .property("enabled", &audio_track::get_enabled, &audio_track::set_enabled)
        .auto_wrap_objects();

    return std::move(conversion);
}
