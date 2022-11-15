#pragma once
#include "ext/array_buffer.hpp"
#include "streams/readable/readable_byte_stream_controller.hpp"
#include "streams/readable/readable_stream.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(streams)
namespace dom::abort {class abort_signal;}
namespace streams::readable {class readable_stream;}
namespace streams::readable {class readable_stream_byob_reader;}
namespace streams::readable {class readable_stream_default_reader;}
namespace streams::writable {class writable_stream;}


namespace streams::detail
{
    auto acquire_readable_stream_stream_byob_reader(
            readable::readable_stream* stream)
             -> std::unique_ptr<readable::readable_stream_byob_reader>;

    auto acquire_readable_stream_default_reader(
            readable::readable_stream* stream)
            -> std::unique_ptr<readable::readable_stream_default_reader>;

    auto create_readable_stream(
            detail::underlying_source_start_callback_t&& start_algorithm,
            detail::underlying_source_pull_callback_t&& pull_algorithm,
            detail::underlying_source_cancel_callback_t&& cancel_algorithm,
            ext::number<int> high_water_mark = 1,
            F3&& size_algorithm = [] {})
            -> std::unique_ptr<readable::readable_stream>;

    auto create_readable_byte_stream(
            detail::underlying_source_start_callback_t&& start_algorithm,
            detail::underlying_source_pull_callback_t&& pull_algorithm,
            detail::underlying_source_cancel_callback_t&& cancel_algorithm)
            -> std::unique_ptr<readable::readable_stream>;

    auto initialize_readable_stream(
            readable::readable_stream* stream)
            -> void;

    auto is_readable_stream_locked(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto readable_stream_pipe_to(
            readable::readable_stream* source,
            writable::writable_stream* destination,
            ext::boolean prevent_close,
            ext::boolean prevent_sbort,
            ext::boolean prevent_cancel,
            dom::abort::abort_signal* signal = nullptr)
            -> ext::promise<void>;

    auto readable_stream_tee(
            readable::readable_stream* stream,
            ext::boolean clone_for_branch_2)
            -> ext::pair<std::unique_ptr<readable::readable_stream>, std::unique_ptr<readable::readable_stream>>;

    auto readable_stream_default_tee(
            readable::readable_stream* stream,
            ext::boolean clone_for_branch_2)
            -> ext::pair<std::unique_ptr<readable::readable_stream>, std::unique_ptr<readable::readable_stream>>;

    auto readable_yte_stream_tee(
            readable::readable_stream* stream)
            -> ext::pair<std::unique_ptr<readable::readable_stream>, std::unique_ptr<readable::readable_stream>>;

    auto readable_stream_add_read_into_request(
            readable::readable_stream* stream,
            read_into_request_t& read_request)
            -> void;

    auto readable_stream_add_read_request(
            readable::readable_stream* stream,
            read_into_request_t& read_request)
            -> void;

    auto readable_stream_cancel(
            readable::readable_stream* stream,
            ext::any reason)
            -> ext::promise<void>; // TODO : web_idl::detail::react should return this type?

    auto readable_stream_close(
            readable::readable_stream* stream)
            -> void;

    auto readable_stream_error(
            readable::readable_stream* stream,
            ext::any error)
            -> void;

    auto readable_stream_fulfill_read_into_request(
            readable::readable_stream* stream,
            chunk_t chunk,
            ext::boolean done)
            -> void;

    auto readable_stream_fulfill_read_request(
            readable::readable_stream* stream,
            chunk_t chunk,
            ext::boolean done)
            -> void;

    auto readable_stream_get_num_read_into_requests(
            readable::readable_stream* stream)
            -> ext::number<size_t>;

    auto readable_stream_get_num_read_requests(
            readable::readable_stream* stream)
            -> ext::number<size_t>;

    auto readable_stream_has_byob_reader(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto readable_stream_has_default_reader(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto readable_stream_reader_generic_cancel(
            readable::readable_stream* stream,
            ext::any reason)
            -> void; // TODO : return type

    auto readable_stream_reader_generic_initialize(
            readable::abstract_readable_stream_reader* reader,
            readable::readable_stream* stream)
            -> void;

    auto readable_stream_reader_generic_release(
            readable::abstract_readable_stream_reader* reader)
            -> void;

    auto readable_stream_byob_reader_error_read_into_requests(
            readable::readable_stream_byob_reader* reader,
            ext::any error)
            -> void;

    auto readable_stream_byob_reader_read(
            readable::readable_stream_byob_reader* reader,
            ext::array_buffer_view& view,
            read_into_request_t& read_request)
            -> void;

    auto readable_stream_byob_reader_release(
            readable::readable_stream_byob_reader* reader)
            -> void;

    auto readable_stream_default_reader_error_read_into_requests(
            readable::readable_stream_default_reader* reader,
            ext::any error)
            -> void;

    auto readable_stream_default_reader_read(
            readable::readable_stream_default_reader* reader,
            read_into_request_t& read_request)
            -> void;

    auto readable_stream_default_reader_release(
            readable::readable_stream_default_reader* reader)
            -> void;

    auto setup_readable_stream_byob_reader(
            readable::readable_stream_byob_reader* reader,
            readable::readable_stream* stream)
            -> void;

    auto setup_readable_stream_default_reader(
            readable::readable_stream_default_reader* reader,
            readable::readable_stream* stream)
            -> void;

    auto readable_stream_default_controller_call_pull_if_needed(
            readable::abstract_readable_stream_controller* controller)
            -> void;

    auto readable_stram_default_controller_should_call_pull(
            readable::readable_stream_default_controller* controller)
            -> ext::boolean;

    auto readable_streaf_default_controller_clear_algorithms(
            readable::readable_stream_default_controller* controller)
            -> void;

    auto readable_stream_default_controller_close(
            readable::readable_stream_default_controller* controller)
            -> void;

    auto readable_stream_default_controller_enqueue(
            readable::readable_stream_default_controller* controller,
            chunk_t chunk)
            -> void;

    auto readable_stream_default_controller_error(
            readable::readable_stream_default_controller* controller,
            ext::any error)
            -> void;

    auto readable_stream_default_controller_get_desired_size(
            readable::readable_stream_default_controller* controller)
            -> ext::number<size_t>; // TODO : return type

    auto readable_stream_default_controller_has_backpressure(
            readable::readable_stream_default_controller* controller)
            -> ext::boolean;

    auto readable_stream_default_controler_can_close_or_enqueue(
            readable::readable_stream_default_controller* controller)
            -> ext::boolean;

    auto setup_readable_stream_default_controller(
            readable::readable_stream* stream,
            readable::readable_stream_default_controller* controller,
            underlying_source_start_callback_t&& start_algorithm,
            underlying_source_pull_callback_t&& pull_algorithm,
            underlying_source_cancel_callback_t&& cancel_callback,
            ext::number<int> high_water_mark, // TODO : type (T)
            size_algorithm_t&& size_algorithm)
            -> void;

    auto setup_readable_stream_default_controller_from_underlying_source(
            readable::readable_stream* stream,
            underlying_source_t&& underlying_source,
            ext::number<int> high_water_mark, // TODO : type (T)
            size_algorithm_t&& size_algorithm)
            -> void;

    auto readable_byte_stream_controller_call_pull_if_needed(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controller_clear_algorithms(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controler_clear_pending_pull_intos(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controller_close(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controller_commit_pull_into_descriptor(
            readable::readable_stream* stream,
            pull_into_descriptor_t& pull_into_descriptor)
            -> void; // TODO : not correct return type

    auto readable_byte_stream_controller_enqueue(
            readable::readable_byte_stream_controller* controller,
            chunk_t chunk)
            -> void;

    auto readable_byte_stream_controller_enqueue_chunk_to_queue(
            readable::readable_byte_stream_controller* controller,
            ext::array_buffer buffer,
            ext::number<size_t> byte_offset, // TODO : type
            ext::number<size_t> byte_length) // TODO : type
            -> void;

    auto readable_byte_stream_controller_enqueue_cloned_chunk_to_queue(
            readable::readable_byte_stream_controller* controller,
            ext::array_buffer buffer,
            ext::number<size_t> byte_offset, // TODO : type
            ext::number<size_t> byte_length) // TODO : type
            -> void;

    auto readable_bytes_stream_controller_enqueued_detached_pull_into_queue(
            readable::readable_byte_stream_controller* controller,
            pull_into_descriptor_t& pull_into_descriptor)
            -> void;

    auto readable_byte_stream_controller_error(
            readable::readable_byte_stream_controller* controller,
            ext::any error)
            -> void;

    auto readable_byte_stream_controller_fill_head_pull_into_descriptor(
            readable::readable_byte_stream_controller* controller,
            ext::number<size_t> size,
            pull_into_descriptor_t& pull_into_descriptor)
            -> void;

    auto readable_byte_stream_controller_fill_pull_into_descriptor_from_queue(
            readable::readable_byte_stream_controller* controller,
            pull_into_descriptor_t& pull_into_descriptor)
            -> void;

    auto readable_byte_stream_controller_fill_read_request_from_queue(
            readable::readable_byte_stream_controller* controller,
            read_request_t& read_request)
            -> void;

    auto readable_byte_stream_controller_get_byob_request(
            readable::readable_byte_stream_controller* controller)
            -> readable::readable_stream_byob_request*;

    auto readable_byte_stream_controller_get_desired_size(
            readable::readable_byte_stream_controller* controller)
            -> ext::number<size_t>;

    auto readable_byte_stream_controller_handle_queue_drain(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controller_invalidates_byob_request(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controller_process_pull_into_descriptors_using_queue(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_strea_controller_process_request_using_queue(
            readable::readable_byte_stream_controller* controller)
            -> void;

    auto readable_byte_stream_controller_pull_into(
            readable::readable_byte_stream_controller* controller,
            ext::array_buffer_view& view,
            read_into_request_t& read_into_request)
            -> void;

    auto readable_byte_stream_controller_responsd(
            readable::readable_byte_stream_controller* controller,
            ext::number<int> bytes_written) // TODO : type
            -> void;

    auto readable_byte_stream_cotroller_response_in_closed_state(
            readable::readable_byte_stream_controller* controller,
            pull_into_descriptor_t& first_descriptor)
            -> void;

    auto readable_byte_stream_controller_response_in_readable_state(
            readable::readable_byte_stream_controller* controller,
            ext::number<int> bytes_written,
            pull_into_descriptor_t& pull_into_descriptor_t)
            -> void;

    auto readable_byte_stream_controller_response_internal(
            readable::readable_byte_stream_controller* controller,
            ext::number<int> bytes_written)
            -> void;

    auto readable_byte_stream_controller_response_with_new_view(
            readable::readable_byte_stream_controller* controller,
            ext::array_buffer_view& view)
            -> void;

    auto readable_byte_stream_controller_shift_pending_pull_into(
            readable::readable_byte_stream_controller* controller)
            -> pull_into_descriptor_t&;

    auto readable_byte_stream_controller_should_call_pull(
            readable::readable_byte_stream_controller* controller)
            -> ext::boolean;

    auto setup_readable_byte_stream_controller(
            readable::readable_stream* stream,
            readable::readable_byte_stream_controller* controller,
            detail::underlying_source_start_callback_t&& start_algorithm,
            detail::underlying_source_pull_callback_t&& pull_algorithm,
            detail::underlying_source_cancel_callback_t&& cancel_algorithm,
            ext::number<int> high_water_mark,
            ext::boolean auto_alocate_chunk_size)
            -> void;

    auto setup_readable_byte_stream_controller_from_underlying_source(
            readable::readable_stream* stream,
            underlying_source_t&& underlying_source,
            ext::number<int> high_water_mark)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
