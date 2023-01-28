module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_default_reader:p;
import apis.streams.mixins.readable_stream_generic_reader;

import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams, readable_stream_default_reader)
        : mixins::readable_stream_generic_reader_private
{
public:
    MAKE_QIMPL(readable_stream_default_reader);
};
