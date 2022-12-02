#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_HPP

#include "streams/readable/abstract_readable_stream_controller.hpp"
namespace streams::readable {class readable_stream_default_controller;}
namespace streams::readable {class readable_stream_default_controller_private;}

#include INCLUDE_INNER_TYPES(streams)
#include "ext/boolean.ixx"
#include "ext/functional.ixx"
#include "ext/number.ixx"
#include "ext/queue.ixx"


class streams::readable::readable_stream_default_controller
        : public abstract_readable_stream_controller
{
public constructors:
    readable_stream_default_controller();
    MAKE_PIMPL(readable_stream_default_controller);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto close() -> void override;
    auto enqueue(detail::chunk_t chunk) -> void override;
    auto error(ext::any error) -> void override;

private js_properties:
    DEFINE_GETTER(desired_size, ext::number<double>) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_HPP
