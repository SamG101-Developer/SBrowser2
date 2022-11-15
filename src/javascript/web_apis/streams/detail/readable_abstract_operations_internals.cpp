#include "readable_abstract_operations_internals.hpp"

#include "streams/detail/miscellaneous_internals.hpp"
#include "streams/readable/readable_stream_byob_reader.hpp"
#include "streams/readable/readable_stream_byob_reader_private.hpp"
#include "streams/readable/readable_stream_default_reader.hpp"
#include "streams/readable/readable_stream_default_reader_private.hpp"


auto streams::detail::acquire_readable_stream_byob_reader(
        readable::readable_stream* stream)
        -> std::unique_ptr<readable::readable_stream_byob_reader>
{
    auto reader = std::make_unique<readable::readable_stream_byob_reader>(stream);
    setup_readable_stream_byob_reader(reader.get(), stream);
    return reader;
}


auto streams::detail::acquire_readable_stream_default_reader(
        readable::readable_stream* stream)
        -> std::unique_ptr<readable::readable_stream_default_reader>
{
    auto reader = std::make_unique<readable::readable_stream_default_reader>(stream);
    setup_readable_stream_default_reader(reader.get(), stream);
    return reader;
}


auto streams::detail::create_readable_stream(
        detail::underlying_source_start_callback_t&& start_algorithm,
        detail::underlying_source_pull_callback_t&& pull_algorithm,
        detail::underlying_source_cancel_callback_t&& cancel_algorithm,
        ext::number<int> high_water_mark,
        detail::size_algorithm_t&& size_algorithm)
        -> std::unique_ptr<readable::readable_stream>
{
    ASSERT ()
}
