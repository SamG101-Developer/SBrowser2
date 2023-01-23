#pragma once
#include "streams/writable/writable_stream_default_controller.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_WRITABLE_ABSTRACT_OPERATIONS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_WRITABLE_ABSTRACT_OPERATIONS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(streams)
namespace streams::writable {class writable_stream;}
namespace streams::writable {class writable_stream_default_controller;}
namespace streams::writable {class writable_stream_default_writer;}


namespace streams::detail
{
    /* SIMPLIFIED */

    auto setup_writable_stream(
            underlying_sink_write_callback_t&& write_algorithm,
            underlying_sink_close_callback_t&& close_algorithm,
            underlying_sink_abort_callback_t&& abort_algorithm,
            high_water_mark_t high_water_mark = 1,
            size_algorithm_t = size_algorithm_t{})
            -> std::unique_ptr<writable::writable_stream>;

    auto error_writable_stream(
            writable::writable_stream* stream,
            ext::any error)
            -> void;

    auto get_writable_stream_signal(
            writable::writable_stream* stream)
            -> dom::abort::abort_signal*;

    auto get_writer(
            writable::writable_stream* stream)
            -> std::unique_ptr<writable::writable_stream_default_writer>;

    auto write_chunk(
            writable::writable_stream_default_writer* writer,
            ext::any chunk)
            -> ext::promise<void>;

    auto release(
            writable::writable_stream_default_writer* writer)
            -> void;

    auto close(
            writable::writable_stream* stream)
            -> ext::promise<void>;

    auto abort(
            writable::writable_stream* stream)
            -> ext::promise<void>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_WRITABLE_ABSTRACT_OPERATIONS_HPP
