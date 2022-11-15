#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace streams::transformable {class transform_stream;}
namespace streams::transformable {class transform_stream_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(streams)


class streams::transformable::transform_stream
        : public dom_object
{
public constructors:
    transform_stream(detail::transformer_t&& transformer, detail::queueing_strategy_t&& writable_strategy = {}, detail::queueing_strategy_t&& readable_strategy = {});
    MAKE_PIMPL(transform_stream);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(readable, readable_stream*);
    DEFINE_GETTER(writable, writable_stream*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_HPP
