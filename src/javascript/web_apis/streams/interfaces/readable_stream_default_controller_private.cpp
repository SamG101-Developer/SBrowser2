module apis.streams.readable_stream_default_controller:p;
import apis.streams.types;

import ext.js;


auto streams::readable_stream_default_controller_private::pull_steps(const detail::read_request_t& request) -> void
{
    if (!queue.empty())
    {
        decltype(auto) chunk = detail::deque_value(this);
        if (close_requested && queue.empty())
        {
            detail::readable_stream_default_controller_clear_algorithm(this);
            detail::readable_stream_close(stream.get());
        }

        else
            detail::readable_stream_default_controller_can_pull_if_needed(this);

        request.chunk_steps(std::move(chunk));
    }

    else
    {
        detail::readable_stream_add_read_request(stream.get(), request);
        detail::readable_stream_default_controller_can_pull_if_needed(this);
    }
}


auto streams::readable_stream_default_controller_private::release_steps() -> void
{
    return;
}


auto streams::readable_stream_default_controller_private::cancel_steps(ext::any&& reason) -> ext::promise<void>>
{
    detail::reset_queue(this);
    auto result = cancel_algorithm(std::move(reason));
    detail::readable_stream_default_controller_clear_algorithm(this);
    return std::move(result);
}
