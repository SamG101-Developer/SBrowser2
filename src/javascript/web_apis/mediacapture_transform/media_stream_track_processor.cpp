#include "media_stream_track_processor.hpp"



#include INCLUDE_INNER_TYPES(dom)


#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_transform/detail/algorithm_internals.hpp"
#include "streams/readable/readable_stream.hpp"


mediacapture::transform::media_stream_track_processor::media_stream_track_processor(
        detail::media_stream_track_processor_init_t&& init)
        : readable{std::make_unique<streams::readable::readable_stream>()}
{
    auto track_option = init.try_emplace("track", nullptr).first->second.to<main::media_stream_track*>();
    auto max_buffer_size_option = init.try_emplace("maxBufferSize", 0).first->second.to<ext::number<int>>();

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [track_option] {return track_option;},
            "Track must be a valid MediaStreamTrack");

    s_track = track_option;
    s_max_buffer_size = ext::max(max_buffer_size_option, 1);
    s_queue = ext::queue<ext::string>{};
    s_num_pending_reads = 0;
    s_is_closed = false;

    streams::detail::setup_readable(readable(), detail::processor_pull, detail::processor_cancel, 0);
}


auto mediacapture::transform::media_stream_track_processor::set_s_track(
        const decltype(s_track)::value_t& val) -> void
{
    guard_property(s_track);
    *s_track = val;

    detail::handle_new_frame(this); // TODO -> is this method called from this setter?
}
