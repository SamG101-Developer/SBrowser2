#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_HPP

#include "streams/readable/abstract_readable_stream_controller.hpp"
namespace streams::readable {class readable_byte_stream_controller;}
namespace streams::readable {class readable_byte_stream_controller_private;}

#include INCLUDE_INNER_TYPES(streams)
namespace streams::readable {class readable_stream_byob_request;}


class streams::readable::readable_byte_stream_controller
        : public abstract_readable_stream_controller
{
public constructors:
    readable_byte_stream_controller();
    MAKE_PIMPL(readable_byte_stream_controller);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto close() -> void override;
    auto enqueue(ext::any chunk) -> void override;
    auto error(ext::any error) -> void override;

private js_properties:
    DEFINE_GETTER(desired_size, ext::number<double>) override;
    DEFINE_GETTER(byob_request, readable_stream_byob_request);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_BYTE_STREAM_CONTROLLER_HPP
