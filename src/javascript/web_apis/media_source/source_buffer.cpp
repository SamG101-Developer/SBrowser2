#include "source_buffer.hpp"
#include "dom/_typedefs.hpp"
#include "source_buffer_private.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "html/basic_media/audio_track.hpp"
#include "html/basic_media/video_track.hpp"
#include "html/basic_media/text_track.hpp"
#include "html/detail/task_internals.hpp"


auto media::source::source_buffer::append_buffer(v8::BufferSource data) -> void
{
    ACCESS_PIMPL(source_buffer);

    detail::prepare_append(this);
    d->input_buffer = data.Buffer()->GetBackingStore()->Data(); // TODO : Concatenate not assign
    d->updating = true;

    dom::detail::queue_task(
            html::detail::dom_manipulation_task_source,
            [this] {dom::detail::fire_event(u"updatestart", this);});

    GO detail::buffer_append;
}


auto media::source::source_buffer::abort() -> void
{
    ACCESS_PIMPL(source_buffer);
    using enum dom::detail::dom_exception_error_t;

    // TODO : Detect if removal has already happened
    // TODO : ready_state
    // TODO : Range removal

    if (d->updating)
    {
        // TODO : abort detail::buffer_append(...) function
        d->updating = false;

        dom::detail::queue_task(
                html::detail::dom_manipulation_task_source,
                [this] {dom::detail::fire_event(u"abort", this);});

        dom::detail::queue_task(
                html::detail::dom_manipulation_task_source,
                [this] {dom::detail::fire_event(u"updateend", this);});
    }

    detail::reset_parser_state();
    d->append_window_start = detail::presentation_start_time();
    d->append_window_end = decltype(d->append_window_end)::inf();
}


auto media::source::source_buffer::get_mode() const -> detail::append_mode_t
{
    ACCESS_PIMPL(const source_buffer);
    return d->mode;
}


auto media::source::source_buffer::get_updating() const -> ext::boolean
{
    ACCESS_PIMPL(const source_buffer);
    return d->updating;
}


auto media::source::source_buffer::get_timestamp_offset() const -> ext::number<double>
{
    ACCESS_PIMPL(const source_buffer);
    return d->timestamp_offset;
}


auto media::source::source_buffer::get_append_window_start() const -> ext::number<double>
{
    ACCESS_PIMPL(const source_buffer);
    return d->append_window_start;
}


auto media::source::source_buffer::get_append_window_end() const -> ext::number<double>
{
    ACCESS_PIMPL(const source_buffer);
    return d->append_window_end;
}


auto media::source::source_buffer::get_buffered() const -> html::basic_media::time_ranges*
{
    ACCESS_PIMPL(const source_buffer);
    return d->buffered.get();
}


auto media::source::source_buffer::get_audio_tracks() const -> ranges::any_helpful_view<html::basic_media::audio_track*>
{
    ACCESS_PIMPL(const source_buffer);
    return d->audio_tracks | ranges::views::transform(&std::unique_ptr<html::basic_media::audio_track>::get);
}


auto media::source::source_buffer::get_video_tracks() const -> ranges::any_helpful_view<html::basic_media::video_track*>
{
    ACCESS_PIMPL(const source_buffer);
    return d->video_tracks | ranges::views::transform(&std::unique_ptr<html::basic_media::video_track>::get);
}


auto media::source::source_buffer::get_text_tracks() const -> ranges::any_helpful_view<html::basic_media::text_track*>
{
    ACCESS_PIMPL(const source_buffer);
    return d->text_tracks | ranges::views::transform(&std::unique_ptr<html::basic_media::text_track>::get);
}
