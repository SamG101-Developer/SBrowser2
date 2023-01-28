module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_byob_request:p;
import apis.dom_object;
import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams::readable, readable_stream_byob_request)
        : dom_object_private
{
public:
    MAKE_QIMPL(readable_stream_byob_request);

public:
    std::observer_ptr<readable_byte_stream_controller> controller;
    ext::array_buffer_view view;
};
