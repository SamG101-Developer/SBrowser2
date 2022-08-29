#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_READER_HPP

#include "streams/readable/abstract_readable_stream_reader.hpp"
namespace streams::readable {class readable_stream_byob_reader;}

#include "ext/promise.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(streams)
namespace streams::readable {class readable_stream;}


class streams::readable::readable_stream_byob_reader
        : public abstract_readable_stream_reader
{
public constructors:
    DOM_CTORS(readable_stream_byob_reader);
    readable_stream_byob_reader() = default;
    explicit readable_stream_byob_reader(readable_stream* stream);

public js_methods:
    auto read(v8::Local<v8::ArrayBufferView> view = {}) -> ext::promise<ext::map<ext::string, ext::any>> override;
    auto release_lock() -> void override;

protected js_slots:
    ext::vector<detail::read_into_request_t> s_read_into_requests;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_READER_HPP
