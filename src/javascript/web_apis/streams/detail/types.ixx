module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.streams.types;
import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE_MIXINS(streams)
{
    class readable_stream_generic_controller;
    class readable_stream_generic_reader;
}


DEFINE_FWD_DECL_NAMESPACE(streams)
{
    class readable_byte_stream_controller;
    class readable_stream;
    class readable_stream_byob_reader;
    class readable_stream_byob_request;
    class readable_stream_default_controller;
    class readable_stream_default_reader;

    class writable_stream;
    class writable_stream_default_controller;
    class writable_stream_default_writer;

    class transform_stream;
    class transform_stream_default_controller;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(streams)
{
    enum class readable_stream_reader_mode_t {BYOB};
    enum class readable_stream_type_t {BYTES};
    enum class readable_stream_state_t {READABLE, CLOSED, ERRORED};
    enum class writable_stream_state_t {WRITABLE, CLOSED, ERRORED, ERRORING};

    struct pull_into_descriptor_t;
    struct read_request_t;
    struct read_into_request_t;
    struct pending_abort_request_t;
    struct closed_sentinel_t;

    // Other
    using chunk_t = ext::any&&;
    using size_algorithm_t = ext::function<ext::number<size_t>(chunk_t chunk)>;
    using strategy_size_algorithm_t = ext::function<ext::number<size_t>()>;

    // Read sources
    using underlying_source_t = ext::map<ext::string, ext::any>;
    using underlying_source_start_callback_t = ext::function<ext::any(mixins::readable_stream_generic_controller* controller)>;
    using underlying_source_pull_callback_t = ext::function<ext::promise<void>(mixins::readable_stream_generic_controller* controller)>;
    using underlying_source_cancel_callback_t = ext::function<ext::promise<void>(ext::any&& reason)>;

    // Write sinks
    using underlying_sink_t = ext::map<ext::string, ext::any>;
    using underlying_sink_start_callback_t = ext::function<ext::any(writable_stream_default_writer* controller)>;
    using underlying_sink_write_callback_t = ext::function<ext::promise<void>(chunk_t chunk, writable_stream_default_controller* controller)>;
    using underlying_sink_close_callback_t = ext::function<ext::promise<void>(ext::any&& reason)>;
    using underlying_sink_abort_callback_t = ext::function<ext::promise<void>(ext::any&& reason)>;

    // Transforming
    using transformer_t = ext::map<ext::string, ext::any>;
    using transform_callback_t = ext::function<ext::promise<void>(chunk_t)>;
    using transform_start_callback_t = ext::function<ext::any(transform_stream_default_controller* controller)>;
    using transform_flush_callback_t = ext::function<ext::promise<void>(transform_stream_default_controller* controller)>;
    using transform_transformer_callback_t = ext::function<ext::promise<void>(chunk_t chunk, transform_stream_default_controller* controller)>;

    // Queuing
    using queueing_strategy_t = ext::map<ext::string, ext::any>;
    using queueing_strategy_init_t = ext::map<ext::string, ext::any>;
    using queueing_strategy_size_t = ext::function<ext::number<double>(chunk_t chunk)>;
    using high_water_mark_t = ext::number<double>;
}
