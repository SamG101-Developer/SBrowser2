module;
#include "ext/macros.hpp"


export module apis.streams.mixins.readable_stream_generic_reader;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(streams::mixins, readable_stream_generic_reader)
        : public virtual dom_object
{
public constructors:
    readable_stream_generic_reader();
    MAKE_PIMPL(readable_stream_generic_reader);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    auto cancel(ext::any&& reason) -> ext::promise<void>;
    virtual auto read(ext::array_buffer_view&& view = {}) -> ext::promise<detail::readable_stream_read_result_t> = 0;
    virtual auto release_lock() -> void = 0;

private js_properties:
    DEFINE_GETTER(closed, ext::promise<void>);
};
