module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_default_controller;
import apis.streams.mixins.readable_stream_generic_controller;


DEFINE_PUBLIC_CLASS(streams, readable_stream_default_controller) final
        : public mixins::readable_stream_generic_controller
{
public constructors:
    readable_stream_default_controller();
    MAKE_PIMPL(readable_stream_default_controller);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto close() -> void override;
    auto enqueue(detail::chunk_t chunk) -> void override;
    auto error(ext::any&& error) -> void override;

private js_properties:
    DEFINE_GETTER(desired_size, ext::number<double>) override;
};
