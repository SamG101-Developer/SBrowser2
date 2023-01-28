module apis.streams.readable_byte_stream_controller:p;
import apis.streams.detail;
import apis.streams.types;

import ext.core;


auto streams::readable_byte_stream_controller_private::pull_steps(const detail::read_request_t& request) -> void
{
    ext::assert_(detail::readable_stream_has_default_reader(this));
    if (queue_total_size > 0)
    {
        ext::assert_(detail::readable_stream_get_num_read_requests(stream) == 0);
        detail::readable_byte_stream_controller_fill_read_request_from_queue(this, request);
        return;
    }

    if (auto_allocate_chunk_size.has_value())
    {
        // TODO
    }

    detail::readable_stream_add_read_request(stream, request);
    detail::readable_byte_stream_controller_call_pull_if_needed(this);
}


auto streams::readable_byte_stream_controller_private::release_steps() -> void
{
    if (!pending_pull_intos.empty())
    {
        decltype(auto) first_pending_pull_into = pending_pull_intos.front();
        first_pending_pull_into.reader_type = nullptr; // TODO
        pending_pull_intos_empty = {first_pending_pull_into}; // TODO : forward?
    }
}


auto streams::readable_byte_stream_controller_private::cancel_steps(ext::any&& reason) -> ext::promise<void>
{
    detail::readable_byte_stream_controller_clear_pending_pull_intos(this);
    detail::reset_queue(this);

    auto result = clear_algorithm(std::move(reason));
    detail::readable_byte_stream_controller_clear_algorithms(this);
    return result;
}
