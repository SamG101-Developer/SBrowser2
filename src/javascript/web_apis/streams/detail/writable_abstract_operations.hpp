#pragma once
#include "streams/writable/writable_stream_default_controller.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_WRITABLE_ABSTRACT_OPERATIONS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_WRITABLE_ABSTRACT_OPERATIONS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(streams)
namespace streams::writable {class writable_stream;}
namespace streams::writable {class writable_stream_default_controller;}
namespace streams::writable {class writable_stream_default_writer;}


namespace streams::detail
{
    auto acquire_writable_stream_default_writer(
            writable::writable_stream* stream)
            -> std::unique_ptr<writable::writable_stream_default_writer>;

    auto create_writable_stream(
            underlying_sink_start_callback_t&& start_algorithm,
            underlying_sink_write_callback_t&& write_algorithm,
            underlying_sink_close_callback_t&& close_algorithm,
            underlying_sink_abort_callback_t&& abort_algorithm,
            high_water_mark_t high_water_mark,
            size_algorithm_t&& size_algorithm)
            -> std::unique_ptr<writable::writable_stream>;

    auto inialize_writable_stream(
            writable::writable_stream* stream)
            -> void;

    auto is_writable_stream_locked(
            writable::writable_stream* stream)
            -> ext::boolean;

    auto setup_writable_stream_default_writer(
            writable::writable_stream_default_writer* writer,
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_abort(
            writable::writable_stream* stream,
            ext::any reason)
            -> ext::promise<void>; // TODO : return type

    auto writable_stream_close(
            writable::writable_stream* stream)
            -> ext::promise<void>;

    auto writable_stream_add_wite_request(
            writable::writable_stream* stream)
            -> ext::promise<void>;

    auto writable_stream_close_queue_or_in_flight(
            writable::writable_stream* stream)
            -> ext::boolean;

    auto writable_stream_deal_with_rejection(
            writable::writable_stream* stream,
            ext::any error)
            -> void;

    auto writable_stream_finish_erroring(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_finish_in_flight_close(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_finish_in_flight_close_with_error(
            writable::writable_stream* stream,
            ext::any error)
            -> void;

    auto writable_stream_finish_in_flight_write(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_finish_in_flight_write_with_error(
            writable::writable_stream* stream,
            ext::any error)
            -> void;

    auto writable_stream_has_operation_marked_in_flight(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_mark_close_request_in_flight(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_mark_first_write_request_in_flight(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_reject_close_and_closed_promise_if_needed(
            writable::writable_stream* stream)
            -> void;

    auto writable_stream_start_erroring(
            writable::writable_stream* stream,
            ext::any reason)
            -> void;

    auto writable_stream_update_backpressure(
            writable::writable_stream* stream,
            backpressure_t backpressure)
            -> void;

    auto writable_stream_default_writer_abort(
            writable::writable_stream_default_writer* writer,
            ext::any reason)
            -> void;

    auto writable_stream_default_writer_close(
            writable::writable_stream_default_writer* writer)
            -> ext::promise<void>; // TODO : return type

    auto writable_stream_default_writer_with_error_propagation(
            writable::writable_stream_default_writer* writer)
            -> ext::promise<void>; // TODO : return type

    auto writable_stream_default_writer_ensure_closed_promise_rejected(
            writable::writable_stream_default_writer* writer,
            ext::any reason)
            -> void;

    auto writable_stream_default_writer_ensure_ready_promise_rejected(
            writable::writable_stream_default_writer* writer,
            ext::any reason)
            -> void;

    auto writable_stream_default_writer_get_desired_size(
            writable::writable_stream_default_writer* writer)
            -> ext::number<size_t>;

    auto writable_stream_default_writer_release(
            writable::writable_stream_default_writer* writer)
            -> void;

    auto writable_stream_default_writer_write(
            writable::writable_stream_default_writer* writer,
            ext::any chunk)
            -> ext::promise<void>;

    auto setup_writable_stream_default_controller(
            writable::writable_stream* stream,
            writable::writable_stream_default_controller* controller,
            underlying_sink_start_callback_t&& start_algorithm,
            underlying_sink_write_callback_t&& write_algorithm,
            underlying_sink_close_callback_t&& close_algorithm,
            underlying_sink_abort_callback_t&& abort_algorithm,
            high_water_mark_t high_water_mark,
            size_algorithm_t&& size_algorithm)
            -> void;

    auto setup_writable_stream_default_controller_from_underlying_sink(
            writable::writable_stream* stream,
            underlying_sink_t&& underlying_sink,
            high_water_mark_t high_water_mark,
            size_algorithm_t&& size_algorithm)
            -> void;

    auto writable_stream_default_controller_advance_queue_if_needed(
            writable::writable_stream_default_controller* controller)
            -> void;

    auto writable_stream_default_controller_clear_algorithms(
            writable::writable_stream_default_controller* controller)
            -> void;

    auto writable_stream_default_controller_close(
            writable::writable_stream_default_controller* controller)
            -> void;

    auto writable_stream_default_controller_error(
            writable::writable_stream_default_controller* controller,
            ext::any error)
            -> void;

    auto writable_stream_default_controller_error_if_needed(
            writable::writable_stream_default_controller* controller,
            ext::any error)
            -> void;

    auto writable_stream_default_controller_get_backpressure(
            writable::writable_stream_default_controller* controller)
            -> ext::boolean;

    auto writable_stream_default_controller_get_chunk_size(
            writable::writable_stream_default_controller* controller,
            ext::any chunk)
            -> ext::number<size_t>;

    auto writable_stream_default_controller_get_desired_size(
            writable::writable_stream_default_controller* controller)
            -> ext::number<size_t>;

    auto writable_stream_default_controller_process_close(
            writable::writable_stream_default_controller* controller)
            -> void;

    auto writable_stream_default_controller_process_write(
            writable::writable_stream_default_controller* controller,
            ext::any chunk)
            -> void;

    auto writable_stream_default_controller_write(
            writable::writable_stream_default_controller* controller,
            ext::any chunk,
            ext::number<size_t> chunk_size)
            -> void;

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
