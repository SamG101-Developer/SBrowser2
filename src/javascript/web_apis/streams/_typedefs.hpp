#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"

namespace streams::readable {class abstract_readable_stream_reader;}
namespace streams::readable {class abstract_readable_stream_controller;}


namespace streams::detail
{
    enum class readable_stream_reader_mode_t {BYOB};
    enum class readable_stream_type_t {BYTES};
    enum class readable_stream_state_t {READABLE, CLOSED, ERRORED};

    struct pull_into_descriptor_t;
    struct read_request_t;
    struct read_into_request_t;

    using readable_stream_get_reader_options_t = ext::map<ext::string, ext::any>;
    using readable_stream_iterator_options_t = ext::map<ext::string, ext::any>;
    using readable_writable_pair_t = ext::map<ext::string, ext::any>;
    using readable_stream_read_result_t = ext::map<ext::string, ext::any>;
    using stream_pipe_options_t = ext::map<ext::string, ext::any>;
    using underlying_source_t = ext::map<ext::string, ext::any>;
    using underlying_source_start_callback_t = ext::function<ext::any(readable::abstract_readable_stream_controller* controller)>;
    using underlying_source_pull_callback_t = ext::function<ext::promise<void>(readable::abstract_readable_stream_controller* controller)>;
    using underlying_source_cancel_callback_t = ext::function<ext::promise<void>(ext::optional<ext::any> reason)>;

    using chunk_t = ext::any;

    using queueing_strategy_t = ext::map<ext::string, ext::any>;
    using queueing_strategy_init_t = ext::map<ext::string, ext::any>;
    using queueing_strategy_size_t = ext::function<ext::number<double>(ext::any chunk)>;
    using high_water_mark_t = ext::number<int>;
    using size_algorithm_t = ext::function<ext::number<size_t>(chunk_t chunk)>;
}


// #include <v8-array-buffer.h>
// namespace streams::readable {class readable_stream_default_controller;}
// namespace streams::readable {class readable_byte_stream_controller;}
// namespace streams::readable {class readable_stream_default_reader;}
// namespace streams::readable {class readable_stream_byob_reader;}
//
// namespace streams::detail
// {
//     enum class readable_stream_reader_mode_t {DEFAULT, BYOB, NONE};
//     enum class readable_stream_type_t {BYTES};
//     enum class readable_stream_state_t {READABLE, CLOSED, ERRORED};
//
//     using chunk_t = char;
//     using error_t = ext::any;
//
//     using readable_stream_controller_t = ext::variant<readable::readable_stream_default_controller*, readable::readable_byte_stream_controller*>;
//     using readable_stream_reader_t = ext::variant<readable::readable_stream_default_reader*, readable::readable_stream_byob_reader*>;
//     using underlying_source_start_callback_t = ext::function<ext::any(readable_stream_controller_t)>;
//     using underlying_source_pull_callback_t = ext::function<ext::promise<void>(readable_stream_controller_t)>;
//     using underlying_source_cancel_callback = ext::function<ext::promise<void>(const ext::any&)>;
//
//     struct read_request_t;
//     struct read_into_request_t;
//
//     struct readable_byte_stream_queue_entry_t;
//     struct pull_into_descriptor_t;
// }
//
//
// struct streams::detail::read_request_t
// {
//     ext::function<void(chunk_t*)> chunk_steps;
//     ext::function<void()> close_steps;
//     ext::function<void(const error_t&)> error_steps;
// };
//
//
// struct streams::detail::read_into_request_t
// {
//     ext::function<void(chunk_t*)> chunk_steps;
//     ext::function<void(chunk_t*)> close_steps;
//     ext::function<void(const error_t&)> error_steps;
// };
//
//
// struct streams::detail::readable_byte_stream_queue_entry_t
// {
//     v8::ArrayBuffer buffer;
//     ext::number<int> byte_offset;
//     ext::number<int> byte_length;
// };
//
//
// struct streams::detail::pull_into_descriptor_t
// {
//     v8::ArrayBuffer buffer;
//     ext::number<int> buffer_byte_length;
//     ext::number<int> byte_offset;
//     ext::number<int> byte_length;
//     ext::number<int> byte_filed;
//     ext::number<int> element_size;
//     v8::DataView view_constructor;
//     readable_stream_reader_mode_t reader_type;
// };

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS__TYPEDEFS_HPP
