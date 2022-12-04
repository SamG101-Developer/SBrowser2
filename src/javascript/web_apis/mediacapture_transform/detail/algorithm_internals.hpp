#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_DETAIL_ALGORITHM_INTERNALS_HPP


namespace mediacapture::transform {class media_stream_track_processor;}

namespace mediacapture::detail
{
    auto maybe_read_frame(
            transform::media_stream_track_processor* processor)
            -> void;

    auto processor_close(
            transform::media_stream_track_processor* processor)
            -> void;

    auto processor_pull(
            transform::media_stream_track_processor* processor)
            -> ext::promise<void>;

    auto processor_cancel(
            transform::media_stream_track_processor* processor)
            -> ext::promise<void>;

    auto handle_new_frame(
            transform::media_stream_track_processor* processor)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_DETAIL_ALGORITHM_INTERNALS_HPP
