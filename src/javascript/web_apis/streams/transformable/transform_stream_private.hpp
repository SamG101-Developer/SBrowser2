#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORM_TRANSFORM_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORM_TRANSFORM_STREAM_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/promise.hpp"
namespace streams::transformable {class transform_stream;}
namespace streams::transformable {class transform_stream_default_controller;}
namespace streams::readable {class readable_stream;}
namespace streams::writable {class writable_stream;}


DEFINE_PRIVATE_CLASS(streams::transformable, transform_stream) : dom_object_private
{
    MAKE_QIMPL(transform_stream);

    ext::boolean detached;
    ext::boolean backpressure;
    ext::promise<void> backpressure_change_promise;

    std::unique_ptr<transformable::transform_stream_default_controller> controller;
    std::unique_ptr<readable::readable_stream> readable;
    std::unique_ptr<writable::writable_stream> writable;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORM_TRANSFORM_STREAM_PRIVATE_HPP
