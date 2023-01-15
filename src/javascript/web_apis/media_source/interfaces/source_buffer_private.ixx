module;
#include "ext/macros.hpp"


export module apis.media_source.source_buffer:p;
import apis.dom.event_target;
import apis.media_source.source_buffer;


DEFINE_PRIVATE_CLASS(media_source, source_buffer) : dom::event_target_private
{
public:
    MAKE_QIMPL(source_buffer);

public:
    detail::append_mode_t mode;
    ext::boolean updating;
    ext::number<double> timestamp_offset;

    ext::number<double> append_window_start;
    ext::number<double> append_window_end;

    std::unique_ptr<html::basic_media::time_ranges> buffered;
    ext::vector<std::unique_ptr<html::basic_media::audio_track>> audio_tracks;
    ext::vector<std::unique_ptr<html::basic_media::video_track>> video_tracks;
    ext::vector<std::unique_ptr<html::basic_media::text_track >> text_tracks;

    void* input_buffer;
    ext::boolean buffer_full_flag;
    ext::number<double> group_start_timestamp;
    ext::number<double> group_end_timestamp;
    ext::boolean generate_timestamps_flag;
};
