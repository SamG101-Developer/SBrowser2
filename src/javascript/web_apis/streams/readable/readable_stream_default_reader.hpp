#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_READER_HPP

#include "streams/readable/abstract_readable_stream_reader.hpp"
namespace streams::readable {class readable_stream_default_reader;}

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(streams)
namespace streams::readable {class readable_stream;}


class streams::readable::readable_stream_default_reader
        : public abstract_readable_stream_reader
{
public constructors:
    DOM_CTORS(readable_stream_default_reader);
    readable_stream_default_reader() = default;
    explicit readable_stream_default_reader(readable_stream* stream);

public js_methods:
    auto read(v8::Local<v8::ArrayBufferView> view = {}) -> ext::promise<ext::map<ext::string, ext::any>> override;
    auto release_lock() -> void override;

private js_slots:
    ext::vector<detail::read_request_t*> s_read_requests;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_READER_HPP
