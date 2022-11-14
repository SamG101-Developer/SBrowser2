#include "algorithm_internals.hpp"

#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "mediacapture_transform/media_stream_track_processor.hpp"

#include "streams/detail/abstract_operations_internals.hpp"
#include "streams/readable/readable_stream.hpp"


auto mediacapture::detail::maybe_read_frame(
        transform::media_stream_track_processor* processor)
        -> void
{
    while (!processor->s_queue().empty() && processor->s_num_pending_reads() != 0)
    {
        streams::detail::enque(processor->s_queue().top());
        processor->s_queue().pop();
        processor->s_num_pending_reads() -= 1;
    }
};


auto mediacapture::detail::processor_close(
        transform::media_stream_track_processor* processor)
        -> void
{
    return_if (processor->s_is_closed());

    streams::detail::close(processor->readable()->s_controller());

    processor->s_track = nullptr;
    processor->s_queue().clear();
    processor->s_is_closed = true;
}


auto mediacapture::detail::processor_pull(
        transform::media_stream_track_processor* processor)
        -> ext::promise<void>
{
    processor->s_num_pending_reads() += 1;
    dom::detail::queue_task(html::detail::media_processor_task_source,
            [processor, maybe_read_frame = std::move(maybe_read_frame)]
            {maybe_read_frame(processor);});

    return ext::promise<void>{}.resolve();
};


auto mediacapture::detail::processor_cancel(
        transform::media_stream_track_processor* processor)
        -> ext::promise<void>
{
    processor_close(processor);
    return ext::promise<void>{}.resolve();
}


auto mediacapture::detail::handle_new_frame(
        transform::media_stream_track_processor* processor)
        -> void
{
    if (processor->s_num_pending_reads() > 0 && processor->s_queue().size() == processor->s_num_pending_reads())
        processor->s_queue().pop();

    processor->s_queue().push(processor->s_track());
    // TODO
}
