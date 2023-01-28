module;
#include "ext/macros.hpp"


export module apis.streams.writable_stream:p;
import apis.dom_object;
import apis.streams.types;


DEFINE_PRIVATE_CLASS(streams, writable_stream)
        : dom_object_private
{
public:
    MAKE_QIMPL(writable_stream);

public:
    ext::boolean backpressure;
    ext::boolean detached;
    ext::promise<void> close_request;
    ext::promise<void> in_flight_write_request;
    ext::promise<void> in_flight_close_request;
    detail::writable_stream_state_t state;
    ext::any stored_error;
    std::unique_ptr<detail::pending_abort_request_t> pending_abort_request;
    std::observer_ptr<writable_stream_default_controller> controller;
    std::observer_ptr<writable_stream_default_writer> writer;
    ext::vector<ext::promise<void>> write_requests;
};
