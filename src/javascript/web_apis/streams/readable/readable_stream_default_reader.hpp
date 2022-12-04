#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_READER_HPP

#include "streams/readable/abstract_readable_stream_reader.hpp"
namespace streams::readable {class readable_stream_default_reader;}
namespace streams::readable {class readable_stream_default_reader_private;}

#include INCLUDE_INNER_TYPES(streams)

namespace streams::readable {class readable_stream;}


class streams::readable::readable_stream_default_reader
        : public abstract_readable_stream_reader
{
public constructors:
    readable_stream_default_reader();
    readable_stream_default_reader(readable_stream* stream);
    MAKE_PIMPL(readable_stream_default_reader);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto read(ext::array_buffer_view&& view = {}) -> ext::promise<detail::readable_stream_read_result_t> override;
    auto release_lock() -> void override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_READER_HPP
