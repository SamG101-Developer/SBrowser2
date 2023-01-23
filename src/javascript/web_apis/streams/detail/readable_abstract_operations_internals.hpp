#pragma once
#include "ext/array_buffer.hpp"
#include "streams/readable/readable_byte_stream_controller.hpp"
#include "streams/readable/readable_stream.hpp"
#include "streams/readable/readable_stream_default_reader.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP



#include INCLUDE_INNER_TYPES(streams)
namespace dom::abort {class abort_signal;}
namespace streams::readable {class readable_stream;}
namespace streams::readable {class readable_stream_byob_reader;}
namespace streams::readable {class readable_stream_default_reader;}
namespace streams::writable {class writable_stream;}


namespace streams::detail
{
    /* SIMPLIFIED */

    auto get_reader(
            readable::readable_stream* stream)
            -> std::unique_ptr<readable::readable_stream_default_reader>;

    auto read_chunk(
            readable::readable_stream_default_reader* reader,
            read_request_t& read_request)
            -> void;

    auto read_all_bytes(
            readable::readable_stream_default_reader* reader)
            -> ext::promise<ext::u8string>;

    auto read_loop(
            readable::readable_stream_default_reader* reader,
            ext::u8string&& bytes,
            ext::promise<ext::u8string> promise)
            -> void;

    auto release(
            readable::readable_stream_default_reader* reader)
            -> ext::promise<void>;

    auto cancel(
            readable::readable_stream_default_reader* reader)
            -> ext::promise<void>;

    auto tee(
            readable::readable_stream_default_reader* reader)
            -> ext::vector<std::unique_ptr<readable::readable_stream>>;

    auto is_readable(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto is_closed(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto is_errored(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto is_locked(
            readable::readable_stream* stream)
            -> ext::boolean;

    auto is_disturbed(
            readable::readable_stream* stream)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
