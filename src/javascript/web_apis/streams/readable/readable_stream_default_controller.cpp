#include "readable_stream_default_controller.hpp"
#include "readable_stream_default_controller_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "streams/detail/readable_abstract_operations_internals.hpp"


auto streams::readable::readable_stream_default_controller::close() -> void
{
    ACCESS_PIMPL(readable_stream_default_controller);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !detail::readable_stream_default_controller_can_close_or_enqueue(this);},
            u8"Readable stream unable to close");

    detail::readable_stream_default_controller_close(this);
}


auto streams::readable::readable_stream_default_controller::enqueue(ext::any chunk) -> void
{
    ACCESS_PIMPL(readable_stream_default_controller);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !detail::readable_stream_default_controller_can_close_or_enqueue(this);},
            u8"Readable stream unable to close");

    detail::readable_stream_default_controller_enqueue(this, chunk);
}


auto streams::readable::readable_stream_default_controller::error(
        ext::any&& error) -> void
{
    detail::readable_stream_default_controller_error(this, std::move(error));
}


auto streams::readable::readable_stream_default_controller::get_desired_size()
        const -> decltype(this->desired_size)::value_t
{
    return detail::readable_stream_default_controller_get_desired_size(this);
}


auto streams::readable::readable_stream_default_controller::s_cancel_steps(
        ext::any&& reason)
        -> void
{
    detail::queue_internals::reset_queue(this);
    auto result = s_cancel_algorithm(std::move(reason));
    detail::readable_stream_default_controller_clear_algorithms(this);
    return result;
}


auto streams::readable::readable_stream_default_controller::s_pull_steps(
        const detail::read_request_t& request)
        -> void
{
    if (!s_queue.empty())
    {
        auto chunk = detail::queue_internals::dequeue_value(this);
        if (s_close_requested && s_queue.empty())
        {
            detail::readable_stream_default_controller_clear_algorithms(this);
            detail::readable_stream_close(s_stream);
        }
        else
            detail::readable_stream_default_controller_call_pull_if_needed(this);

        request.chunk_steps(chunk);
    }

    else
    {
        detail::readable_stream_add_read_request(s_stream, request);
        detail::readable_stream_default_contrller_can_pull_if_needed(this);
    }
}
