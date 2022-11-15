#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORM_TRANSFORM_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORM_TRANSFORM_STREAM_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
namespace streams::transformable {class transform_stream;}


DEFINE_PRIVATE_CLASS(streams::transformable, transform_stream) : dom_object_private
{
    MAKE_QIMPL(transform_stream);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_TRANSFORM_TRANSFORM_STREAM_PRIVATE_HPP
