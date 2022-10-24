#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(media_source)
namespace html::basic_media {class time_ranges;}
namespace html::basic_media {class audio_track;}
namespace html::basic_media {class video_track;}
namespace html::basic_media {class text_track;}


DEFINE_PRIVATE_CLASS(media::source, source_buffer) : dom::nodes::event_target_private
{
    detail::append_mode_t mode;
    ext::boolean updating;
    ext::number<double> timestamp_offset;

    ext::number<double> append_window_start;
    ext::number<double> append_window_end;

    std::unique_ptr<html::basic_media::time_ranges> buffered;
    ext::vector<std::unique_ptr<html::basic_media::audio_track>> audio_tracks;
    ext::vector<std::unique_ptr<html::basic_media::video_track>> video_tracks;
    ext::vector<std::unique_ptr<html::basic_media::text_track >> text_tracks;

    ext::boolean generate_timestamps_flag;

    void* input_buffer;
    ext::boolean buffer_full_flag;
    ext::number<double> group_start_timestamp;
    ext::number<double> group_end_timestamp;
    ext::boolean generate_timestamps_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_PRIVATE_HPP
