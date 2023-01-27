module;
#include "ext/macros.hpp"


export module apis.streams.mixins.readable_stream_generic_reader:p;
import apis.dom_object;

import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams::mixins, readable_stream_generic_reader)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(readable_stream_generic_reader);

public:
    ext::promise<void> closed_promise;
    std::observer_ptr<readable_stream> stream; // TODO : unique_ptr<>?
};
