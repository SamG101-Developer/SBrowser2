#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_READER_HPP

#include "streams/mixins/readable_stream_generic_reader.hpp"
namespace streams::readable {class abstract_readable_stream_reader;}
namespace streams::readable {class abstract_readable_stream_reader_private;}

#include INCLUDE_INNER_TYPES(streams)
#include "ext/array_buffer.hpp"


class streams::readable::abstract_readable_stream_reader
        : public mixins::readable_stream_generic_reader
{
public constructors:
    abstract_readable_stream_reader();
    MAKE_PIMPL(abstract_readable_stream_reader);
    MAKE_V8_AVAILABLE;

public js_methods:
    virtual auto read(ext::array_buffer_view&& view = {}) -> ext::promise<detail::readable_stream_read_result_t> = 0;
    virtual auto release_lock() -> void = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_READER_HPP
