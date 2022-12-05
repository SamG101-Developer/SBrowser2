#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(streams)




namespace streams::readable {class readable_stream;}


DEFINE_PRIVATE_CLASS(streams::readable, abstract_readable_stream_controller) : virtual dom_object_private
{
    ext::function<ext::promise<void>(ext::any)> cancel_algorithm;
    ext::function<ext::promise<void>()> pull_algorithm;
    ext::boolean close_requested;
    ext::boolean pull_again;
    ext::boolean pulling;
    ext::boolean started;
    ext::number<int> strategy_hwm;
    ext::queue<detail::chunk_t> queue;
    ext::number<size_t> queue_total_size;
    readable_stream* stream;

    virtual auto pull_steps(const detail::read_request_t& request) -> void = 0;
    virtual auto release_steps() -> void = 0;
    virtual auto cancel_steps(ext::any reason) -> void = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_ABSTRACT_READABLE_STREAM_CONTROLLER_PRIVATE_HPP
