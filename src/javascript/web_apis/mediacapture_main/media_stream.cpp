#include "media_stream.hpp"

#include "ext/uuid.hpp"
#include "ext/ranges.hpp"

#include "mediacapture_main/media_stream_track.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/view/any_view.hpp>


mediacapture::main::media_stream::media_stream()
        : m_track_set{}
        , id{ext::to_string(ext::uuid_system_generator{}())}
{}


mediacapture::main::media_stream::media_stream(
        mediacapture::main::media_stream* stream)
        : media_stream{}
{
    // set the track set to the track set of the MediaStream parameter
    m_track_set = stream->m_track_set;
}


mediacapture::main::media_stream::media_stream(
        ext::vector<media_stream_track*>&& tracks)
        : media_stream{}
{
    // set the track set to the track set parameter
    m_track_set = ext::set<media_stream_track*>{
        std::make_move_iterator(tracks.begin()),
        std::make_move_iterator(tracks.end())};
}


auto mediacapture::main::media_stream::get_tracks()
        const -> ranges::any_view<media_stream_track*>
{
    // return a live range to the track set
    return ranges::any_view<media_stream_track*>{m_track_set};
}


auto mediacapture::main::media_stream::get_audio_tracks()
        const -> ranges::any_view<media_stream_track*>
{
    // return live range of the track set whose kind is "audio"
    using enum ranges::views::filter_compare_t;
    return m_track_set
            | ranges::views::filter_eq<EQ>(&media_stream_track::kind, "audio");
}


auto mediacapture::main::media_stream::get_video_tracks()
        const -> ranges::any_view<media_stream_track*>
{
    // return live range of the track set whose kind is "video"
    using enum ranges::views::filter_compare_t;
    return m_track_set
            | ranges::views::filter_eq<EQ>(&media_stream_track::kind, "video");
}


auto mediacapture::main::media_stream::get_track_by_id(
        ext::string_view track_id)
        const -> media_stream_track*
{
    // return the first track (of any type), whose 'id' matches the 'track_id' parameter - if there are no matching
    // tracks, then a nullptr is returned, mapping to a Null object in JavaScript
    using enum ranges::views::filter_compare_t;
    auto matching_tracks = m_track_set
            | ranges::views::filter_eq<EQ>(&media_stream_track::id, track_id);

    return matching_tracks.begin();
}


auto mediacapture::main::media_stream::add_track(
        media_stream_track* track)
        -> void
{
    m_track_set.insert(track);
}


auto mediacapture::main::media_stream::remove_track(
        media_stream_track* track)
        -> void
{
    m_track_set |= ranges::actions::remove(track);
}


auto mediacapture::main::media_stream::clone()
        const -> media_stream
{
    media_stream stream_clone{m_track_set
            | ranges::views::transform(&media_stream_track::clone)
            | ranges::to<ext::vector<media_stream_track*>>};
}
