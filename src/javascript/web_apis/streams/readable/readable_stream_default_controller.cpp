#include "readable_stream_default_controller.hpp"
#include "readable_stream_default_controller_private.hpp"




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


auto streams::readable::readable_stream_default_controller::error(ext::any error) -> void
{
    detail::readable_stream_default_controller_error(this, std::move(error));
}


auto streams::readable::readable_stream_default_controller::get_desired_size() const -> ext::number<double>
{
    return detail::readable_stream_default_controller_get_desired_size(this);
}
