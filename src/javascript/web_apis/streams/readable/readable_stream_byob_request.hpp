#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_HPP

#include "dom_object.hpp"
namespace streams::readable {class readable_stream_byob_request;}
namespace streams::readable {class readable_stream_byob_request_private;}

#include "ext/array_buffer.hpp"
namespace streams::readable {class readable_byte_stream_controller;}


class streams::readable::readable_stream_byob_request
        : public virtual dom_object
{
public constructors:
    readable_stream_byob_request();
    MAKE_PIMPL(readable_stream_byob_request);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto respond(ext::number<ulonglong> bytes_written) -> void;
    auto respond_with_new_view(ext::array_buffer_view&& view) -> void;

private js_properties:
    DEFINE_GETTER(view, ext::array_buffer_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_REQUEST_HPP
