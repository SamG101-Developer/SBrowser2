module;
#include "ext/macros.hpp"


export module apis.streams.writable_stream;
import apis.dom_object;

import apis.streams.types;
import ext.js;


DEFINE_PUBLIC_CLASS(streams, writable_stream) final
        : public dom_object
{
public constructors:
    writable_stream(detail::underlying_sink_t&& underlying_sink = {}, detail::queueing_strategy_t&& strategy = {});
    MAKE_PIMPL(writable_stream);
    MAKE_TRANSFERABLE(writable_stream);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto abort(ext::any&& reason) -> ext::promise<void>;
    auto close() -> ext::promise<void>;
    auto get_writer() -> writable_stream_default_writer*;

public js_properties:
    DEFINE_GETTER(locked, ext::boolean);
};
