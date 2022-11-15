#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
namespace streams::writable {class writable_stream_default_controller;}


DEFINE_PRIVATE_CLASS(streams::writable, writable_stream_default_controller) : dom_object_private
{
    MAKE_QIMPL(writable_stream_default_controller);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_WRITABLE_WRITABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
