#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS__TYPEDEFS_HPP

#include <future>
#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <v8-array-buffer.h>
namespace streams::readable {class readable_stream_default_controller;}
namespace streams::readable {class readable_byte_stream_controller;}
namespace streams::readable {class readable_stream_default_reader;}
namespace streams::readable {class readable_stream_byob_reader;}

namespace streams::detail
{
    enum class readable_stream_reader_mode_t {DEFAULT, BYOB, NONE};
    enum class readable_stream_type_t {BYTES};
    enum class readable_stream_state_t {READABLE, CLOSED, ERRORED};

    using chunk_t = char;
    using error_t = ext::any;

    using readable_stream_controller_t = ext::variant<readable::readable_stream_default_controller*, readable::readable_byte_stream_controller*>;
    using readable_stream_reader_t = ext::variant<readable::readable_stream_default_reader*, readable::readable_stream_byob_reader*>;
    using underlying_source_start_callback_t = ext::function<ext::any(readable_stream_controller_t)>;
    using underlying_source_pull_callback_t = ext::function<std::promise<void>(readable_stream_controller_t)>;
    using underlying_source_cancel_callback = ext::function<std::promise<void>(const ext::any&)>;

    struct read_request_t;
    struct read_into_request_t;

    struct readable_byte_stream_queue_entry_t;
    struct pull_into_descriptor_t;
}


struct streams::detail::read_request_t
{
    ext::function<void(chunk_t*)> chunk_steps;
    ext::function<void()> close_steps;
    ext::function<void(const error_t&)> error_steps;
};


struct streams::detail::read_into_request_t
{
    ext::function<void(chunk_t*)> chunk_steps;
    ext::function<void(chunk_t*)> close_steps;
    ext::function<void(const error_t&)> error_steps;
};


struct streams::detail::readable_byte_stream_queue_entry_t
{
    v8::ArrayBuffer buffer;
    ext::number<int> byte_offset;
    ext::number<int> byte_length;
};


struct streams::detail::pull_into_descriptor_t
{
    v8::ArrayBuffer buffer;
    ext::number<int> buffer_byte_length;
    ext::number<int> byte_offset;
    ext::number<int> byte_length;
    ext::number<int> byte_filed;
    ext::number<int> element_size;
    v8::DataView view_constructor;
    readable_stream_reader_mode_t reader_type;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS__TYPEDEFS_HPP
