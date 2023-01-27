module;
#include "ext/macros.hpp"


export module apis.streams.readable_stream_byob_reader:p;
import apis.streams.mixins.readable_stream_generic_reader;
import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams::readable, readable_stream_byob_reader)
        : mixins::readable_stream_generic_reader_private
{
public:
    MAKE_QIMPL(readable_stream_byob_reader);

public:
    ext::vector<std::unique_ptr<detail::read_into_request_t>> read_into_requests;
};
