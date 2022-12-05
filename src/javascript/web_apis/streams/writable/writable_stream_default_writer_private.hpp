#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_WRITER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_WRITER_PRIVATE_HPP

#include "ext/pimpl.ixx"

namespace streams::writable {class writable_stream_default_writer;}


namespace streams::writable {class writable_stream;}


DEFINE_PRIVATE_CLASS(streams::writable, writable_stream_default_writer) : dom_object_private
{
    MAKE_QIMPL(writable_stream_default_writer);

    ext::promise<void> closed_promise;
    ext::promise<void> ready_promise;
    std::observer_ptr<writable_stream> stream;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_WRITER_PRIVATE_HPP
