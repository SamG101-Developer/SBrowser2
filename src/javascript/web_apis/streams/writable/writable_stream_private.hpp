#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_PRIVATE_HPP

#include "ext/pimpl.ixx"

namespace streams::writable {class writable_stream;}



namespace streams::writable {class writable_stream_default_controller;}
namespace streams::writable {class writable_stream_default_writer;}


DEFINE_PRIVATE_CLASS(streams::writable, writable_stream) : dom_object_private
{
    MAKE_QIMPL(writable_stream);

    ext::boolean backpressure;
    ext::boolean detached;
    ext::promise<void> close_request;
    ext::promise<void> in_flight_write_request;
    ext::promise<void> in_flight_close_request;
    detail::writable_stream_state_t state;
    ext::any stored_error;
    std::unique_ptr<pending_abort_request_t> pending_abort_request;
    std::observer_ptr<writable_stream_default_controller> controller;
    std::observer_ptr<writable_stream_default_writer> writer;
    ext::vector<ext::promise<void>> write_requests;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_PRIVATE_HPP
