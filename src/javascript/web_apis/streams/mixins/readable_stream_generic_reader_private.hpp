#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"

namespace streams::readable {class readable_stream;}


DEFINE_PRIVATE_CLASS(streams::mixins, readable_stream_generic_reader) : virtual dom_object_private
{
    ext::promise<void> closed_promise;
    std::observer_ptr<readable::readable_stream> stream;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_MIXINS_READABLE_STREAM_GENERIC_READER_PRIVATE_HPP
