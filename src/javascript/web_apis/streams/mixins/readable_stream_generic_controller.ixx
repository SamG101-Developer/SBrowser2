module;
#include "ext/macros.hpp"


export module apis.streams.mixins.readable_stream_generic_controller;
import apis.dom_object;

import apis.streams.types;


DEFINE_PUBLIC_CLASS(streams, readable_stream_generic_controller)
        : public dom_object
{
public constructors:
    readable_stream_generic_controller();
    MAKE_PIMPL(readable_stream_generic_controller);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    virtual auto close() -> void = 0;
    virtual auto enqueue(detail::chunk_t chunk) -> void = 0;
    virtual auto error(ext::any&& error) -> void = 0;

private js_properties:
    virtual DEFINE_GETTER(desired_size, ext::number<double>) = 0;
};
