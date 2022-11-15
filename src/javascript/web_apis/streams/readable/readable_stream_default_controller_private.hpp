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
    auto cancel_steps(ext::any reason) -> void override;
};


// auto streams::readable::readable_stream_default_controller::s_cancel_steps(
//         ext::any&& reason)
//         -> void
// {
//     detail::queue_internals::reset_queue(this);
//     auto result = s_cancel_algorithm(std::move(reason));
//     detail::readable_stream_default_controller_clear_algorithms(this);
//     return result;
// }
//
//
// auto streams::readable::readable_stream_default_controller::s_pull_steps(
//         const detail::read_request_t& request)
//         -> void
// {
//     if (!s_queue.empty())
//     {
//         auto chunk = detail::queue_internals::dequeue_value(this);
//         if (s_close_requested && s_queue.empty())
//         {
//             detail::readable_stream_default_controller_clear_algorithms(this);
//             detail::readable_stream_close(s_stream);
//         }
//         else
//             detail::readable_stream_default_controller_call_pull_if_needed(this);
//
//         request.chunk_steps(chunk);
//     }
//
//     else
//     {
//         detail::readable_stream_add_read_request(s_stream, request);
//         detail::readable_stream_default_contrller_can_pull_if_needed(this);
//     }
// }


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_READABLE_READABLE_STREAM_DEFAULT_CONTROLLER_PRIVATE_HPP
