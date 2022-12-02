#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/array_buffer.hpp"
#include "ext/memory.ixx"
namespace streams::readable {class readable_byte_stream_controller;}


DEFINE_PRIVATE_CLASS(streams::readable, readable_stream_byob_request) : dom_object_private
{
    MAKE_QIMPL(readable_stream_byob_request);

    std::observer_ptr<readable_byte_stream_controller> controller;
    ext::array_buffer_view view;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_PRIVATE_HPP
