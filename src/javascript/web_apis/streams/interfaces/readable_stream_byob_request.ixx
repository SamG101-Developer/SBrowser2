module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_byob_request;
import apis.dom_object;

import ext.js;


DEFINE_PUBLIC_CLASS(streams, readable_stream_byob_request) final
        : public virtual dom_object
{
public constructors:
    readable_stream_byob_request();
    MAKE_PIMPL(readable_stream_byob_request);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    auto respond(ext::number<ulonglong> bytes_written) -> void;
    auto respond_with_new_view(ext::array_buffer_view&& view) -> void;

private js_properties:
    DEFINE_GETTER(view, ext::array_buffer_view);
};
