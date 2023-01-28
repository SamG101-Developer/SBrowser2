module;
#include "ext/macros.hpp"


export module apis.streams.detail;

import apis.dom.types;
import apis.streams.types;

import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(streams)
{
    // [4.9.1] - Working with readable streams
    auto acquire_readable_stream_byob_reader(readable_stream* stream) -> std::unique_ptr<readable_stream_byob_reader>;
    auto acquire_readable_stream_default_reader(readable_stream* stream) -> std::unique_ptr<readable_stream_default_reader>;
    auto create_readable_stream(underlying_source_start_callback_t&& start_algorithm, underlying_source_pull_callback_t&& pull_algorithm, underlying_source_cancel_callback_t&& cancel_algorithm, high_water_mark_t high_water_mark = 1, size_algorithm_t&& size_algorithm = [](chunk_t) {return 1;}) -> std::unique_ptr<readable_stream>;
    auto create_readable_byte_stream(detail::underlying_source_start_callback_t&& start_algorithm, detail::underlying_source_pull_callback_t&& pull_algorithm, detail::underlying_source_cancel_callback_t&& cancel_algorithm) -> std::unique_ptr<readable_stream>;
    auto initialize_readable_stream(readable_stream* stream) -> void;
    auto is_readable_stream_locked(readable_stream* stream) -> ext::boolean;
    auto readable_stream_pipe_to(readable_stream* source, writable_stream* destination, ext::boolean prevent_close, ext::boolean prevent_abort, ext::boolean prevent_cancel, dom::abort_signal* signal = nullptr) -> ext::promise<void>;
    auto readable_stream_tee(readable_stream* stream, ext::boolean clone_for_branch_2) -> ext::vector<std::unique_ptr<readable_stream>>;
    auto readable_stream_default_tee(readable_stream* stream, ext::boolean clone_for_branch_2) -> ext::vector<std::unique_ptr<readable_stream>>;
    auto readable_byte_stream_tee(readable_stream* stream) -> ext::vector<std::unique_ptr<readable_stream>>;

    // [4.9.2] Interfacing with controllers
    auto readable_stream_add_read_request(readable_stream* stream, std::unique_ptr<read_request_t>&& read_request) -> void;
    auto readable_stream_cancel(readable_stream* stream, ext::any&& reason) -> ext::promise<void>;
    auto readable_stream_close(readable_stream* stream) -> void;
    auto readable_stream_error(readable_stream* stream, ext::any&& error) -> void;
    auto readable_stream_fulfill_read_request(readable_stream* stream, chunk_t chunk, ext::boolean done) -> void;
    auto readable_stream_get_num_read_requests(readable_stream* stream) -> ext::number<size_t>;
    auto readable_stream_has_byob_reader(readable_stream* stream) -> ext::boolean;
    auto readable_stream_has_default_reader(readable_stream* stream) -> ext::boolean;

    // [4.9.3] Readers
    auto readable_stream_reader_generic_cancel(readable_stream* stream, ext::any&& reason) -> ext::promise<void>;
    auto readable_stream_reader_generic_initialize(mixins::readable_stream_generic_reader* reader, readable_stream* stream) -> void;
    auto readable_stream_reader_generic_release(mixins::readable_stream_generic_reader* reader) -> void;
    auto readable_stream_byob_reader_error_read_into_requests(readable_stream_byob_reader* reader, ext::any&& error) -> void;
    auto readable_stream_byob_reader_read(readable_stream_byob_reader* reader, ext::array_buffer_view& view, read_request_t& read_request) -> void;
    auto readable_stream_byob_reader_release(readable_stream_byob_reader* reader) -> void;
    auto readable_stream_default_reader_error_read_requests(readable_stream_default_reader* reader, ext::any&& error) -> void;
    auto readable_stream_default_reader_read(readable_stream_default_reader* reader, read_request_t& read_request) -> void;
    auto readable_stream_default_reader_release(readable_stream_default_reader* reader) -> void;
    auto setup_readable_stream_byob_reader(readable_stream_byob_reader* reader, readable_stream* stream) -> void;
    auto setup_readable_stream_default_reader(readable_stream_default_reader* reader, readable_stream* stream) -> void;
    
    // [4.9.4] Default controllers
    auto readable_stream_default_controller_call_pull_if_needed(abstract_readable_stream_controller* controller) -> void;
    auto readable_stream_default_controller_should_call_pull(readable_stream_default_controller* controller) -> ext::boolean;
    auto readable_stream_default_controller_clear_algorithms(readable_stream_default_controller* controller) -> void;
    auto readable_stream_default_controller_close(readable_stream_default_controller* controller) -> void;
    auto readable_stream_default_controller_enqueue(readable_stream_default_controller* controller, chunk_t chunk) -> void;
    auto readable_stream_default_controller_error(readable_stream_default_controller* controller, ext::any&& error) -> void;
    auto readable_stream_default_controller_get_desired_size(readable_stream_default_controller* controller) -> ext::number<size_t>;
    auto readable_stream_default_controller_has_backpressure(readable_stream_default_controller* controller) -> ext::boolean;
    auto readable_stream_default_controller_can_close_or_enqueue(readable_stream_default_controller* controller) -> ext::boolean;
    auto setup_readable_stream_default_controller(readable_stream* stream, readable_stream_default_controller* controller, underlying_source_start_callback_t&& start_algorithm, underlying_source_pull_callback_t&& pull_algorithm, underlying_source_cancel_callback_t&& cancel_callback, ext::number<int> high_water_mark, size_algorithm_t&& size_algorithm) -> void;
    auto setup_readable_stream_default_controller_from_underlying_source(readable_stream* stream, underlying_source_t&& underlying_source, high_water_mark_t high_water_mark, size_algorithm_t&& size_algorithm) -> void;

    // [4.9.5] Byte stream controllers
    auto readable_byte_stream_controller_call_pull_if_needed(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_clear_algorithms(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_clear_pending_pull_intos(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_close(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_commit_pull_into_descriptor(readable_stream* stream, pull_into_descriptor_t& pull_into_descriptor) -> void;
    auto readable_byte_stream_controller_convert_pull_into_descriptor(pull_into_descriptor_t& pull_into_descriptor) -> void;
    auto readable_byte_stream_controller_enqueue(readable_byte_stream_controller* controller, chunk_t chunk) -> void;
    auto readable_byte_stream_controller_enqueue_chunk_to_queue(readable_byte_stream_controller* controller, ext::array_buffer buffer, ext::number<size_t> byte_offset, ext::number<size_t> byte_length) -> void;
    auto readable_byte_stream_controller_enqueue_cloned_chunk_to_queue(readable_byte_stream_controller* controller, ext::array_buffer buffer, ext::number<size_t> byte_offset, ext::number<size_t> byte_length) -> void;
    auto readable_byte_stream_controller_enqueue_detached_pull_into_queue(readable_byte_stream_controller* controller, pull_into_descriptor_t& pull_into_descriptor) -> void;
    auto readable_byte_stream_controller_error(readable_byte_stream_controller* controller, ext::any&& error) -> void;
    auto readable_byte_stream_controller_fill_head_pull_into_descriptor(readable_byte_stream_controller* controller, ext::number<size_t> size, pull_into_descriptor_t& pull_into_descriptor) -> void;
    auto readable_byte_stream_controller_fill_pull_into_descriptor_from_queue(readable_byte_stream_controller* controller, pull_into_descriptor_t& pull_into_descriptor) -> void;
    auto readable_byte_stream_controller_fill_read_request_from_queue(readable_byte_stream_controller* controller, read_request_t& read_request) -> void;
    auto readable_byte_stream_controller_get_byob_request(readable_byte_stream_controller* controller) -> readable_stream_byob_request*;
    auto readable_byte_stream_controller_get_desired_size(readable_byte_stream_controller* controller) -> ext::number<size_t>;
    auto readable_byte_stream_controller_handle_queue_drain(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_invalidates_byob_request(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_process_pull_into_descriptors_using_queue(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_process_request_using_queue(readable_byte_stream_controller* controller) -> void;
    auto readable_byte_stream_controller_pull_into(readable_byte_stream_controller* controller, ext::array_buffer_view& view, read_into_request_t& read_into_request) -> void;
    auto readable_byte_stream_controller_respond(readable_byte_stream_controller* controller, ext::number<int> bytes_written) -> void;
    auto readable_byte_stream_controller_respond_in_closed_state(readable_byte_stream_controller* controller, pull_into_descriptor_t& first_descriptor) -> void;
    auto readable_byte_stream_controller_respond_in_readable_state(readable_byte_stream_controller* controller, ext::number<int> bytes_written, pull_into_descriptor_t& pull_into_descriptor_t) -> void;
    auto readable_byte_stream_controller_respond_internal(readable_byte_stream_controller* controller, ext::number<int> bytes_written) -> void;
    auto readable_byte_stream_controller_respond_with_new_view(readable_byte_stream_controller* controller, ext::array_buffer_view& view) -> void;
    auto readable_byte_stream_controller_shift_pending_pull_into(readable_byte_stream_controller* controller) -> pull_into_descriptor_t&;
    auto readable_byte_stream_controller_should_call_pull(readable_byte_stream_controller* controller) -> ext::boolean;
    auto setup_readable_byte_stream_controller(readable_stream* stream, readable_byte_stream_controller* controller, detail::underlying_source_start_callback_t&& start_algorithm, detail::underlying_source_pull_callback_t&& pull_algorithm, detail::underlying_source_cancel_callback_t&& cancel_algorithm, ext::number<int> high_water_mark, ext::optional<ext::number<int>> auto_alocate_chunk_size = ext::nullopt) -> void;
    auto setup_readable_byte_stream_controller_from_underlying_source(readable_stream* stream, underlying_source_t&& underlying_source, high_water_mark_t high_water_mark) -> void;

    // [5.5.1] Working with writable streams
    auto acquire_writable_stream_default_writer(writable_stream* stream) -> std::unique_ptr<writable_stream_default_writer>;
    auto create_writable_stream(underlying_sink_start_callback_t&& start_algorithm, underlying_sink_write_callback_t&& write_algorithm, underlying_sink_close_callback_t&& close_algorithm, underlying_sink_abort_callback_t&& abort_algorithm, high_water_mark_t high_water_mark, size_algorithm_t&& size_algorithm) -> std::unique_ptr<writable_stream>;
    auto initialize_writable_stream(writable_stream* stream) -> void;
    auto is_writable_stream_locked(writable_stream* stream) -> ext::boolean;
    auto setup_writable_stream_default_writer(writable_stream_default_writer* writer, writable_stream* stream) -> void;
    auto writable_stream_abort(writable_stream* stream, ext::any&& reason) -> ext::promise<void>;
    auto writable_stream_close(writable_stream* stream) -> ext::promise<void>;

    // [5.5.2] Interfacing with controllers
    auto writable_stream_add_wite_request(writable_stream* stream) -> ext::promise<void>;
    auto writable_stream_close_queued_or_in_flight(writable_stream* stream) -> ext::boolean;
    auto writable_stream_deal_with_rejection(writable_stream* stream, ext::any&& error) -> void;
    auto writable_stream_finish_erroring(writable_stream* stream) -> void;
    auto writable_stream_finish_in_flight_close(writable_stream* stream) -> void;
    auto writable_stream_finish_in_flight_close_with_error(writable_stream* stream, ext::any&& error) -> void;
    auto writable_stream_finish_in_flight_write(writable_stream* stream) -> void;
    auto writable_stream_finish_in_flight_write_with_error(writable_stream* stream, ext::any&& error) -> void;
    auto writable_stream_has_operation_marked_in_flight(writable_stream* stream) -> void;
    auto writable_stream_mark_close_request_in_flight(writable_stream* stream) -> void;
    auto writable_stream_mark_first_write_request_in_flight(writable_stream* stream) -> void;
    auto writable_stream_reject_close_and_closed_promise_if_needed(writable_stream* stream) -> void;
    auto writable_stream_start_erroring(writable_stream* stream, ext::any&& reason) -> void;
    auto writable_stream_update_backpressure(writable_stream* stream, ext::boolean backpressure) -> void;

    // [5.5.3] Writers
    auto writable_stream_default_writer_abort(writable_stream_default_writer* writer, ext::any&& reason) -> void;
    auto writable_stream_default_writer_close(writable_stream_default_writer* writer) -> ext::promise<void>;
    auto writable_stream_default_writer_with_error_propagation(writable_stream_default_writer* writer) -> ext::promise<void>;
    auto writable_stream_default_writer_ensure_closed_promise_rejected(writable_stream_default_writer* writer, ext::any&& reason) -> void;
    auto writable_stream_default_writer_ensure_ready_promise_rejected(writable_stream_default_writer* writer, ext::any&& reason) -> void;
    auto writable_stream_default_writer_get_desired_size(writable_stream_default_writer* writer) -> ext::number<size_t>;
    auto writable_stream_default_writer_release(writable_stream_default_writer* writer) -> void;
    auto writable_stream_default_writer_write(writable_stream_default_writer* writer, ext::any&& chunk) -> ext::promise<void>;
    
    // [5.5.4] Default controllers
    auto setup_writable_stream_default_controller(writable_stream* stream, writable_stream_default_controller* controller, underlying_sink_start_callback_t&& start_algorithm, underlying_sink_write_callback_t&& write_algorithm, underlying_sink_close_callback_t&& close_algorithm, underlying_sink_abort_callback_t&& abort_algorithm, high_water_mark_t high_water_mark, size_algorithm_t&& size_algorithm) -> void;
    auto setup_writable_stream_default_controller_from_underlying_sink(writable_stream* stream, underlying_sink_t&& underlying_sink, high_water_mark_t high_water_mark, size_algorithm_t&& size_algorithm) -> void;
    auto writable_stream_default_controller_advance_queue_if_needed(writable_stream_default_controller* controller) -> void;
    auto writable_stream_default_controller_clear_algorithms(writable_stream_default_controller* controller) -> void;
    auto writable_stream_default_controller_close(writable_stream_default_controller* controller) -> void;
    auto writable_stream_default_controller_error(writable_stream_default_controller* controller, ext::any&& error) -> void;
    auto writable_stream_default_controller_error_if_needed(writable_stream_default_controller* controller, ext::any&& error) -> void;
    auto writable_stream_default_controller_get_backpressure(writable_stream_default_controller* controller) -> ext::boolean;
    auto writable_stream_default_controller_get_chunk_size(writable_stream_default_controller* controller, ext::any&& chunk) -> ext::number<size_t>;
    auto writable_stream_default_controller_get_desired_size(writable_stream_default_controller* controller) -> ext::number<size_t>;
    auto writable_stream_default_controller_process_close(writable_stream_default_controller* controller) -> void;
    auto writable_stream_default_controller_process_write(writable_stream_default_controller* controller, ext::any&& chunk) -> void;
    auto writable_stream_default_controller_write(writable_stream_default_controller* controller, ext::any&& chunk, ext::number<size_t> chunk_size) -> void;

    // [6.4.1] Working with writable streams
    auto initialize_transform_stream(transform_stream* stream, ext::promise<void>&& start_promise, high_water_mark_t writable_high_water_mark, size_algorithm_t&& writable_size_algorithm, high_water_mark_t readable_high_water_mark, size_algorithm_t&& readable_size_algorithm) -> void;
    auto transform_stream_error(transform_stream* stream, ext::any&& error) -> void;
    auto transform_stream_error_writable_and_unblock_write(transform_stream* stream, ext::any&& error) -> void;
    auto transform_stream_set_backpressure(transform_stream* stream, ext::boolean backpressure) -> void;

    // [6.4.2] Default controllers
    auto setup_transform_stream_default_controller(transform_stream* stream, transform_stream_default_controller* controller, transform_callback_t&& transform_algorithm, transform_flush_callback_t&& flush_algortithm) -> void;
    auto setup_transform_stream_default_controller_from_transformer(transform_stream* stream, void* transformer, transformer_t&& transformer_dict) -> void;
    auto transform_stream_default_controller_clear_algorithms(transform_stream_default_controller* controller) -> void;
    auto transform_stream_default_controller_enqueue(transform_stream_default_controller* controller, chunk_t chunk) -> void;
    auto transform_stream_default_controller_error(transform_stream_default_controller* controller, ext::any&& error) -> void;
    auto transform_stream_default_controller_perform_transform(transform_stream_default_controller* controller, chunk_t chunk) -> void;
    auto transform_stream_default_controller_terminate(transform_stream_default_controller* controller) -> void;

    // [6.4.3] Default sinks
    auto transform_stream_default_sink_write_algorithm(transform_stream* stream, chunk_t chunk) -> ext::promise<void>;
    auto transform_stream_default_sink_abort_algorithm(transform_stream* stream, ext::any&& reason) -> ext::promise<void>;
    auto transform_stream_default_sink_close_algorithm(transform_stream* stream) -> ext::promise<void>;

    // [6.4.4] Default sources
    auto transform_stream_default_source_pull_algorithm(transform_stream* stream) -> ext::boolean;

    // [7.4.0] Queuing strategies
    auto extract_high_water_mark(queueing_strategy_t&& strategy, high_water_mark_t default_hwm) -> high_water_mark_t;
    auto extract_size_algorithm(queueing_strategy_t&& strategy) -> size_algorithm_t;

    // [8.1.0] Queue with sizes
    template <typename T> auto dequeue_value(T&& container) -> chunk_t;
    template <typename T> auto enqueue_value_with_size(T&& container, chunk_t value, size_t size) -> void;
    template <typename T> auto peek_queue_value(T&& container) -> chunk_t;
    template <typename T> auto reset_queue(T&& container) -> void;

    // [8.2.0] Transferable streams
    template <typename T> auto cross_realm_transform_send_error(ext::number<int> port, T&& error) -> void;
    template <typename T, typename U> auto pack_and_post_message(ext::number<int> port, T&& type, U&& value) -> void;
    template <typename T, typename U> auto pack_and_post_message_handling_error(ext::number<int> port, T&& type, U&& value) -> void;
    auto setup_cross_realm_transform_readable(readable_stream* stream, ext::number<int> port) -> void;
    auto setup_cross_realm_transform_writable(writable_stream* stream, ext::number<int> port) -> void;

    // [8.3.0] Miscellaneous
    auto can_transfer_array_buffer(v8::Local<v8::ArrayBuffer> O)-> ext::boolean;
    auto is_non_negative_number(v8::Local<v8::Value> V) -> ext::boolean;
    auto transfer_array_buffer(v8::Local<v8::ArrayBuffer> O) -> v8::Local<v8::ArrayBuffer>;
    auto clone_as_uint8array(v8::Local<v8::Object> O)-> v8::Local<v8::Uint8Array>;
    auto structured_clone(v8::Local<v8::Object> V) -> v8::Local<v8::String>;

    // [9.1.1] Creation and manipulation
    auto setup_newly_created_readable_stream(readable_stream* stream, pull_algorithm_t&& pull_algorithm, cancel_algorithm_t&& cancel_algorithm, high_water_mark_t high_water_mark = 1, size_algorithm_t size_algorithm = size_algorithm_t{}) -> void;
    auto setup_with_byte_reading_support(readable_stream* stream, pull_algorithm_t&& pull_algorithm, cancel_algorithm_t&& cancel_algorithm, high_water_mark_t high_water_mark = 0) -> void;
    auto readable_stream_desired_size_to_fill_up_to_high_water_mark(readable_stream* stream) -> ext::number<int>;
    auto close_readable_stream(readable_stream* stream) -> void;
    auto error_readable_stream(readable_stream* stream) -> void;
    auto enqueue_chunk_into_readable_stream(readable_stream* stream) -> void;
    auto current_byob_request_view_for_readable_stream(readable_stream* stream) -> readable_stream_byob_request;

    // [9.1.2] Reading
    auto get_reader(readable_stream* stream) -> std::unique_ptr<readable_stream_default_reader>;
    auto read_chunk(readable_stream_default_reader* reader, read_request_t& read_request) -> void;
    auto read_all_bytes(readable_stream_default_reader* reader) -> ext::promise<ext::u8string>;
    auto read_loop(readable_stream_default_reader* reader, ext::u8string&& bytes, ext::promise<ext::u8string> promise) -> void;
    auto release(readable_stream_default_reader* reader) -> ext::promise<void>;
    auto cancel(readable_stream_default_reader* reader, ext::any&& reason) -> ext::promise<void>;
    auto cancel(readable_stream* stream, ext::any&& reason) -> void;
    auto tee(readable_stream_default_reader* reader) -> ext::vector<std::unique_ptr<readable_stream>>;
    
    // [9.1.3] Introspection
    auto is_readable(readable_stream* stream) -> ext::boolean;
    auto is_closed(readable_stream* stream) -> ext::boolean;
    auto is_errored(readable_stream* stream) -> ext::boolean;
    auto is_locked(readable_stream* stream) -> ext::boolean;
    auto is_disturbed(readable_stream* stream) -> ext::boolean;

    // [9.2.1] Creation and manipulation
    auto setup_newly_created_writable_stream(underlying_sink_write_callback_t&& write_algorithm, underlying_sink_close_callback_t&& close_algorithm, underlying_sink_abort_callback_t&& abort_algorithm, high_water_mark_t high_water_mark = 1, size_algorithm_t = size_algorithm_t{}) -> std::unique_ptr<writable_stream>;
    auto error_writable_stream(writable_stream* stream, ext::any error) -> void;
    auto signal_of_writable_stream(writable_stream* stream) -> dom::abort_signal*;

    // [9.2.2] Writing
    auto get_writer(writable_stream* stream) -> std::unique_ptr<writable_stream_default_writer>;
    auto write_chunk(writable_stream_default_writer* writer, ext::any&& chunk) -> ext::promise<void>;
    auto release(writable_stream_default_writer* writer) -> void;
    auto close(writable_stream* stream) -> ext::promise<void>;
    auto abort(writable_stream* stream) -> ext::promise<void>;

    // [9.3.1] Creation and manipulation
    auto setup_newly_created_transform_stream(transform_stream* stream, transform_callback_t&& transform_algorithm, transform_flush_callback_t&& transform_flush_callback) -> void;
    auto create_identity_transform_stream() -> std::unique_ptr<transform_stream>;
    auto enqueue_into_transform_stream(transform_stream* stream, chunk_t chunk) -> void;
    auto terminate_transform_stream(transform_stream* stream) -> void;
    auto error_transform_stream(transform_stream* stream) -> void;

    // [9.5]
    auto readable_stream_piped_to_writable_stream(readable_stream* readable, writable_stream* writable, ext::boolean prevent_close = false, ext::boolean prevent_abort = false, ext::boolean prevent_cancel = false, dom::abort_signal* signal = nullptr) -> ext::promise<void>;
    auto readable_stream_piped_through_writable_stream(readable_stream* readable, writable_stream* writable, ext::boolean prevent_close = false, ext::boolean prevent_abort = false, ext::boolean prevent_cancel = false, dom::abort_signal* signal = nullptr) -> ext::promise<void>;
    auto create_proxy_readable_stream() -> std::unique_ptr<readable_stream>;
}
