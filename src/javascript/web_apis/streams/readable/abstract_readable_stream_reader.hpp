#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_READER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_READER_HPP

#include "streams/mixins/readable_stream_generic_reader.hpp"
namespace streams::readable {class abstract_readable_stream_reader;}

class streams::readable::abstract_readable_stream_reader
        : public mixins::readable_stream_generic_reader
{
public js_methods:
    virtual auto read(v8::Local<v8::ArrayBufferView> view = {}) -> ext::promise<ext::map<ext::string, ext::any>> = 0;
    virtual auto release_lock() -> void = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_READER_HPP
