#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(streams)
#include "ext/any.hpp"
#include "ext/boolean.hpp"


DEFINE_PRIVATE_CLASS(streams::readable, readable_steam) : virtual dom_object_private
{
    detail::readable_stream_reader_t reader;
    detail::readable_stream_controller_t controller;
    ext::boolean detached;
    ext::boolean disturbed;
    detail::readable_stream_state_t state;
    ext::any error;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_PRIVATE_HPP
