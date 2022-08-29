#include "file_reader.hpp"
#include "file_api/detail/file_internals.hpp"


auto file_api::file_reader::read_as_array_buffer(
        blob* blob_object)
        -> void
{
    detail::read_operation(this, blob_object); // TODO
}


auto file_api::file_reader::read_as_text(
        file_api::blob* blob_object,
        ext::string_view encoding)
        -> void
{
    detail::read_operation(this, blob_object, encoding); // TODO
}


auto file_api::file_reader::read_as_data_url(
        file_api::blob* blob_object)
        -> void
{
    detail::read_operation(this, blob_object); // TODO
}


auto file_api::file_reader::abort()
        -> void
{
    if (ready_state() == EMPTY || ready_state() == DONE)
        return static_cast<void>(result = "");

    if (ready_state() == LOADING)
        ext::tie(ready_state, result) = ext::make_tuple(DONE, "");

    // TODO : task source stuff
    // TODO : algorithm termination

    detail::fire_progress_event("abort", this);
    if (ready_state() != LOADING)
        detail::fire_progress_event("loadend", this);
}
