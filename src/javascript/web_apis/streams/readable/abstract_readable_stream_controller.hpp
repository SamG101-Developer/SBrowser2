#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_HPP

#include "dom_object.hpp"
namespace streams::readable {class abstract_readable_stream_controller;}
namespace streams::readable {class abstract_readable_stream_controller_private;}

#include INCLUDE_INNER_TYPES(streams)
namespace streams::readable {class readable_stream;}


class streams::readable::abstract_readable_stream_controller
        : public virtual dom_object
{
public constructors:
    abstract_readable_stream_controller();
    MAKE_PIMPL(abstract_readable_stream_controller);
    MAKE_V8_AVAILABLE;

public js_methods:
    virtual auto close() -> void = 0;
    virtual auto enqueue(detail::chunk_t chunk) -> void = 0;
    virtual auto error(ext::any error) -> void = 0;

private js_properties:
    virtual DEFINE_GETTER(desired_size, ext::number<double>) = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_HPP
