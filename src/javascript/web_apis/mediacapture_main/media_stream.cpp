#include "media_stream.hpp"
#include "media_stream_private.hpp"

#include "ext/functional.ixx"
#include "ext/uuid.ixx"
#include "ext/ranges.hpp"

#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_main/media_stream_track_private.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/view/any_view.hpp>


mediacapture::main::media_stream::media_stream()
{
    INIT_PIMPL(media_stream);

    ACCESS_PIMPL(media_stream);
    d->id = ext::to_string(ext::uuid::uuid_system_generator{}()); // TODO : create static generator
}


mediacapture::main::media_stream::media_stream(
        mediacapture::main::media_stream* stream)
        : media_stream{}
{
    // set the track set to the track set of the MediaStream parameter - this is a modified copy constructor that takes
    // a pointer (all DomObjects are used as pointers, but saved on created on the stack), and copies the track set into
    // this MediaStream object
    ACCESS_PIMPL(media_stream);
    d->track_set = stream->d_func()->track_set;
}


mediacapture::main::media_stream::media_stream(
        ext::vector<media_stream_track*>&& tracks)
        : media_stream{}
{
    // set the track set to the 'track' parameter - the parameter is a vector, but the iterators are moved into the set
    // being stored by this MediaStream object
    ACCESS_PIMPL(media_stream);
    d->track_set = ext::set<media_stream_track*>{std::make_move_iterator(tracks.begin()), std::make_move_iterator(tracks.end())};
}


auto mediacapture::main::media_stream::get_tracks()
        const -> ranges::any_view<media_stream_track*, ranges::category::forward>
{
    // return a live range to the track set
    ACCESS_PIMPL(const media_stream);
    return ranges::any_view<media_stream_track*, ranges::category::forward>{d->track_set};
}


auto mediacapture::main::media_stream::get_audio_tracks()
        const -> ranges::any_view<media_stream_track*, ranges::category::forward>
{
    // return live range of the track set whose kind is "audio" (the predicate formula is to `invoke` the property to
    // get its value)
    ACCESS_PIMPL(const media_stream);
    using enum ranges::filter_compare_t;
    return d->track_set
            | ranges::views::filter_eq<EQ>(&media_stream_track_private::kind, u"audio", ext::get_pimpl);
}


auto mediacapture::main::media_stream::get_video_tracks()
        const -> ranges::any_view<media_stream_track*, ranges::category::forward>
{
    // return live range of the track set whose kind is "video" (the predicate formula is to `invoke` the property to
    // get its value)
    ACCESS_PIMPL(const media_stream);
    using enum ranges::filter_compare_t;
    return d->track_set
            | ranges::views::filter_eq<EQ>(&media_stream_track_private::kind, u"video", ext::get_pimpl);
}


auto mediacapture::main::media_stream::get_track_by_id(
        ext::string_view track_id)
        const -> media_stream_track*
{
    // return the first track (of any type), whose 'id' matches the 'track_id' parameter - if there are no matching
    // tracks, then a nullptr is returned, mapping to a Null object in JavaScript
    ACCESS_PIMPL(const media_stream);
    using enum ranges::filter_compare_t;
    auto matching_tracks = d->track_set
            | ranges::views::filter_eq<EQ>(&media_stream_track_private::id, track_id, ext::get_pimpl);

    return matching_tracks.front();
}


auto mediacapture::main::media_stream::add_track(
        media_stream_track* track)
        -> void
{
    ACCESS_PIMPL(media_stream);
    d->track_set.emplace(track);
}


auto mediacapture::main::media_stream::remove_track(
        media_stream_track* track)
        -> void
{
    ACCESS_PIMPL(media_stream);
    d->track_set |= ranges::actions::remove(track);
}


auto mediacapture::main::media_stream::clone() const -> media_stream
{
    ACCESS_PIMPL(const media_stream);
    return {d->track_set
            | ranges::views::transform(&media_stream_track::clone)
            | ranges::to<ext::vector<media_stream_track*>>()};
}


auto mediacapture::main::media_stream::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const media_stream);
    return d->id;
}


auto mediacapture::main::media_stream::get_active() const -> ext::boolean
{
    return detail::active(this);
}
