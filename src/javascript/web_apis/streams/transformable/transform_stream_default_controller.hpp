#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_DEFAULT_CONTROLLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_DEFAULT_CONTROLLER_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace streams::transformable {class transform_stream_default_controller;}
namespace streams::transformable {class transform_stream_default_controller_private;}

// Other Includes & Forward Declarations


class streams::transformable::transform_stream_default_controller
        : public dom_object
{
public constructors:
    transform_stream_default_controller();
    MAKE_PIMPL(transform_stream_default_controller);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto enqueue(ext::any chunk) -> void;
    auto error(ext::any chunk) -> void;
    auto terminate() -> void;

public js_properties:
    DEFINE_GETTER(desired_size, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_DEFAULT_CONTROLLER_HPP
