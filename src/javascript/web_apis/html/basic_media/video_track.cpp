#include "video_track.hpp"
#include "video_track_private.hpp"

#include "html/basic_media/abstract_track.hpp"


auto html::basic_media::video_track::get_selected() const -> ext::boolean
{
    ACCESS_PIMPL(const video_track);
    return d->selected;
}


auto html::basic_media::video_track::set_selected(ext::boolean new_selected) -> ext::boolean
{
    ACCESS_PIMPL(video_track);
    return d->selected = new_selected;
}


auto html::basic_media::video_track::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<video_track>{isolate}
        .inherit<abstract_track>()
        .property("selected", &video_track::get_selected, &video_track::set_selected)
        .auto_wrap_objects();

    return std::move(conversion);
}
