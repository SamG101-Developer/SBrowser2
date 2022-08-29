#include "file_internals.hpp"

#include USE_INNER_TYPES(dom)
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "file_api/file_reader.hpp"
#include "file_api/detail/blob_internals.hpp"

#include "html/detail/task_internals.hpp"

#include "streams/readable/readable_stream.hpp"


auto file_api::detail::read_operation(
        file_reader* file_reader,
        blob* blob,
        ext::string_view optional_encoding_name)
        -> ext::promise<ext::string>
{
    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [file_reader] {return file_reader->ready_state() == file_reader->LOADING;},
            "File is already loading");

    file_reader->ready_state = file_reader->LOADING;
    file_reader->result = "";
    file_reader->error = nullptr;

    auto stream = get_stream(blob);
    auto reader = streams::detail::get_reader(&stream);
    auto chunk_promise = streams::detail::read_chunk(&stream, &reader);
    auto is_first_chunk = ext::boolean::TRUE_();

    go [file_reader, &is_first_chunk]
    {
        while (true)
        {
            while (!chunk_promise.is_resolved() || chunk_promise.is_rejected) continue;
            if (is_first_chunk && chunk_promise.is_resolved)
                dom::detail::queue_task(
                        html::detail::file_reading_task_source,
                        ext::bind_front{fire_progress_event, "loadstart", file_reader});

            is_first_chunk = false;
            // TODO : streams API needs finishing first
        }
    };
}
