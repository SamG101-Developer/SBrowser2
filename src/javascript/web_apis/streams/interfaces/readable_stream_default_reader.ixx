module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_default_reader;
import apis.dom_object;
import apis.streams.mixins.readable_stream_generic_reader;

import apis.streams.types;
import ext.js;


DEFINE_PUBLIC_CLASS(streams, readable_stream_default_reader) final
        : public dom_object
        , public mixins::readable_stream_generic_reader
{
public constructors:
    readable_stream_default_reader();
    readable_stream_default_reader(readable_stream* stream);
    MAKE_PIMPL(readable_stream_default_reader);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto read(ext::array_buffer_view&& view = {}) -> ext::promise<readable_stream_read_result_t> override;
    auto release_lock() -> void override;
};
