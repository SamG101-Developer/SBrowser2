#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_READER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_READER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "abstract_readable_stream_reader_private.hpp"

#include INCLUDE_INNER_TYPES(streams)
#include "ext/vector.hpp"


DEFINE_PRIVATE_CLASS(streams::readable, readable_stream_byob_reader) : abstract_readable_stream_reader_private
{
    ext::vector<std::unique_ptr<detail::read_into_request_t>> read_into_requests;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_BYOB_READER_PRIVATE_HPP
