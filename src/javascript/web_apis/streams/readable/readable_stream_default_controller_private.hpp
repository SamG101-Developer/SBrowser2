#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "abstract_readable_stream_controller_private.hpp"


DEFINE_PRIVATE_CLASS(streams::readable, readable_stream_default_controller) : abstract_readable_stream_controller_private
{
    ext::function<ext::number<int>(ext::queue<detail::chunk_t>)> strategy_size_algorithm;

    auto pull_steps(const detail::read_request_t& request) -> void override;
    auto release_steps() -> void override;
    auto cancel_steps(ext::any&& reason) -> void override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
