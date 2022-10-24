#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/concepts.hpp"
#include "ext/optional.hpp"
#include "ext/variant.hpp"
#include INCLUDE_INNER_TYPES(media_source)
namespace dom::nodes {class window;}
namespace html::workers {class dedicated_worker_global_scope;}
namespace media::source {class media_source;}
namespace media::source {class source_buffer;}


namespace media::detail
{
    auto attach_to_media_element(
            source::media_source* source)
            -> void;

    auto detach_from_media_element(
            source::media_source* source)
            -> void;

    auto seek()
            -> void;

    auto monitor_source_buffer(
            source::source_buffer* source_buffer)
            -> void;

    auto selected_track_state_changes()
            -> void;

    auto duration_change()
            -> void;

    auto end_of_stream(
            source::media_source* media_source,
            ext::optional<detail::end_of_stream_error_t>)
            -> void;

    template <ext::callable F>
    auto mirror_if_necessary(
            ext::variant<dom::nodes::window*, html::workers::dedicated_worker_global_scope*> global,
            F&& steps)
            -> void;

    auto segment_parse_loop(
            source::source_buffer* source_buffer)
            -> void;

    auto reset_parser_state(
            source::source_buffer* source_buffer)
            -> void;

    auto append_error(
            source::source_buffer* source_buffer)
            -> void;

    auto prepare_append(
            source::source_buffer* source_buffer)
            -> void;

    auto buffer_append(
            source::source_buffer* source_buffer)
            -> void;

    auto range_removal(
            source::source_buffer* source_buffer)
            -> void;

    auto initialization_segment_received(
            source::source_buffer* source_buffer)
            -> void;

    auto coded_frame_processing()
            -> void;

    auto coded_frame_removal()
            -> void;

    auto coded_frame_eviction()
            -> void;

    auto audio_splice_rendering()
            -> void;

    auto text_splice_frame()
            -> void;

    // TODO : HTMLMediaElement::seekable custom getter steps defined by this spec
    // TODO : HTMLMediaElement::buffered custom getter steps defined by this spec
    // TODO : HTMLMediaElement::src_object custom getter steps defined by this spec
    //
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_DETAIL_ALGORITHM_INTERNALS_HPP
