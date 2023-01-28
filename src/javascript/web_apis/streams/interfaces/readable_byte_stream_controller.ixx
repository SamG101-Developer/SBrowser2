module;
#include "ext/macros.hpp"


export module apis.streams.readable_byte_stream_controller;
import apis.streams.mixins.readable_stream_generic_controller;


DEFINE_PUBLIC_CLASS(streams, readable_byte_stream_controller) final
        : public mixins::readable_stream_generic_controller
{
public constructors:
    readable_byte_stream_controller();
    MAKE_PIMPL(readable_byte_stream_controller);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto close() -> void override;
    auto enqueue(ext::any chunk) -> void override;
    auto error(ext::any error) -> void override;

private js_properties:
    DEFINE_GETTER(desired_size, ext::number<double>) override;
    DEFINE_GETTER(byob_request, readable_stream_byob_request*);
};
