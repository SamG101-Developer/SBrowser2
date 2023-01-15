module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>
#include <swl/variant.hpp>


export module apis.media_source.detail;

import apis.dom.types;
import apis.media_source.types;
import ext.core;


// TODO : move some to private class functions


DEFINE_FWD_DECL_NAMESPACE_DETAIL(media_source)
{
    auto attach_to_media_element(
            media_source* source)
            -> void;

    auto detach_from_media_element(
            media_source* source)
            -> void;

    auto seek()
            -> void;

    auto monitor_source_buffer(
            source_buffer* source_buffer)
            -> void;

    auto selected_track_state_changes()
            -> void;

    auto duration_change()
            -> void;

    auto end_of_stream(
            media_source* media_source,
            ext::optional<end_of_stream_error_t>)
            -> void;

    template <ext::callable F>
    auto mirror_if_necessary(
            ext::variant<dom::window*, html::dedicated_worker_global_scope*> global,
            F&& steps)
            -> void;

    auto segment_parse_loop(
            source_buffer* source_buffer)
            -> void;

    auto reset_parser_state(
            source_buffer* source_buffer)
            -> void;

    auto append_error(
            source_buffer* source_buffer)
            -> void;

    auto prepare_append(
            source_buffer* source_buffer)
            -> void;

    auto buffer_append(
            source_buffer* source_buffer)
            -> void;

    auto range_removal(
            source_buffer* source_buffer)
            -> void;

    auto initialization_segment_received(
            source_buffer* source_buffer)
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
};
