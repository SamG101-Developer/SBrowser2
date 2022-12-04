#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"
namespace streams::transformable {class transform_stream_default_controller;}



namespace streams::transformable {class transform_stream;}


DEFINE_PRIVATE_CLASS(streams::transformable, transform_stream_default_controller) : dom_object_private
{
    MAKE_QIMPL(transform_stream_default_controller);

    ext::function<ext::promise<void>()> flush_algorithm;
    ext::function<ext::promise<void>()> transform_algorithm;
    std::observer_ptr<transform_stream> stream;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORMABLE_TRANSFORM_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
