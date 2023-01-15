module;
#include "ext/macros.hpp"
#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/cache1.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/to_container.hpp>


module apis.media_source.media_source;

import apis.dom.dom_exception;
import apis.dom.detail;
import apis.dom.types;

import ext.core;


auto media_source::media_source::add_source_buffer(ext::string_view type) -> source_buffer*
{
    ACCESS_PIMPL(media_source);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&type] {return type.empty();},
            u8"Source buffer type can not be empty");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [&type] {return !mimesniff::detail::valid_mime_type(type);},
            u8"Source buffer type is an invalid mime-type");

    dom::detail::throw_v8_exception<QUOTA_EXCEEDED_ERR>(
            [&type] {return false; /* TODO */;},
            u8"");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->ready_state != detail::ready_state_t::OPEN;},
            u8"State must be 'open'");

    auto buffer = std::make_unique<source_buffer>();
    buffer->d_func()->generate_timestamps_flag = mse::byte_stream_format_registry::registry(mimesniff::detail::parse_mime_type(type)).generate_timestamps_flag;
    buffer->d_func()->mode = buffer->d_func()->generate_timestamps_flag ? detail::append_mode_t::SEQUENCE : detail::append_mode_t::SEGMENTS;
    d->source_buffers.push_back(std::move(buffer));

    auto event_fire = BIND_FRONT(dom::detail::queue_task,
            html::detail::dom_manipulation_task_source,
            [d](source_buffer* target) {dom::detail::fire_event(u"addsourcebuffer", target);});

    d->source_buffers
            | ranges::views::transform(&std::unique_ptr<media_source>::get)
            | ranges::views::for_each(event_fire);

    return d->source_buffers.back().get();
}


auto media::source::media_source::remove_source_buffer(source_buffer* buffer) -> void
{
    ACCESS_PIMPL(media_source);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<NOT_FOUND_ERR>(
            [d, buffer]
            {
                return !ranges::contains(
                        d->source_buffers,
                        buffer,
                        &std::unique_ptr<source_buffer>::get);
            },
            u8"'source_buffer' not fouund in the 'buffers' list");

    if (buffer->d_func()->updating)
    {
        // TODO: abort buffer_append() if its running
        buffer->d_func()->updating = false;

        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [buffer] {dom::detail::fire_event(u"abort", buffer);});

        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [buffer] {dom::detail::fire_event(u"updateend", buffer);});
    }

    for (decltype(auto) audio_track: buffer->d_func()->audio_tracks)
    {
        auto e = js::env::env::current();
        audio_track->d_func()->source_buffer = nullptr;
        buffer->d_func()->audio_tracks |= ranges::actions::remove(std::move(audio_track));
        detail::mirror_if_necessary(
                e.cpp.global<dom::nodes::window*>(),
                [&audio_tracks = buffer->d_func()->audio_tracks, audio_track = std::move(audio_track)] mutable
                {audio_tracks |= ranges::actions::remove(std::move(audio_track));});
    }

    for (decltype(auto) video_track: buffer->d_func()->video_tracks)
    {
        auto e = js::env::env::current();
        video_track->d_func()->source_buffer = nullptr;
        buffer->d_func()->video_tracks |= ranges::actions::remove(std::move(video_track));
        detail::mirror_if_necessary(
                e.cpp.global<dom::nodes::window*>(),
                [&video_tracks = buffer->d_func()->video_tracks, video_track = std::move(video_track)] mutable
                {video_tracks |= ranges::actions::remove(std::move(video_track));});
    }

    for (decltype(auto) text_track: buffer->d_func()->text_tracks)
    {
        auto e = js::env::env::current();
        text_track->d_func()->source_buffer = nullptr;
        buffer->d_func()->text_tracks |= ranges::actions::remove(std::move(text_track));
        detail::mirror_if_necessary(
                e.cpp.global<dom::nodes::window*>(),
                [&text_tracks = buffer->d_func()->text_tracks, text_track = std::move(text_track)] mutable
                {text_tracks |= ranges::actions::remove(std::move(text_track));});
    }

    if (ranges::contains(d->active_source_buffers, buffer))
    {
        d->active_source_buffers |= ranges::actions::remove(buffer);
        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [active_buffers = d->active_source_buffers]
                {dom::detail::fire_event(u"removesourcebuffer", active_buffers);});
    }

    d->source_buffers |= ranges::actions::remove(buffer);
    dom::detail::queue_task(html::detail::dom_manipulation_task_source,
            [active_buffers = buffers]
            {dom::detail::fire_event(u"removesourcebuffer", active_buffers);});

    // TODO: Destroy all resources for sourceBuffer. (where is unique_ptr<source_buffer> stored?)
}


auto media::source::media_source::end_of_stream(ext::optional<detail::end_of_stream_error_t> error) -> void
{
    ACCESS_PIMPL(media_source);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->ready_state != detail::ready_state_t::OPEN;},
            u8"State must be 'open'");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return ranges::any_of(
                    d->source_buffers
                            | ranges::views::transform([](auto&& buffer) {return buffer->d_func()->updating;}), BIND_FRONT(ext::cmp::eq, true));
            },
            u8"Cannot end a stream that contains updating buffers");

    detail::end_of_stream(this, error);
}


auto media::source::media_source::set_live_seekable_range(
        ext::number<double> start,
        ext::number<double> end)
        -> void
{
    ACCESS_PIMPL(media_source);
    using enum v8_primitive_error_t;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->ready_state != detail::ready_state_t::OPEN;},
            u8"State must be 'open'");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&start, &end] {return start < 0 || start > end;},
            u8"'start' must be positive and less than 'end'");

    d->live_seekable_range = std::make_unique<html::basic_media::time_ranges>();
    d->live_seekable_range->d_func()->linked_vector->emplace_back(start, end);
}


auto media::source::media_source::clear_live_seekable_range() -> void
{
    ACCESS_PIMPL(media_source);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->ready_state != detail::ready_state_t::OPEN;},
            u8"State must be 'open'");

    d->live_seekable_range = std::make_unique<html::basic_media::time_ranges>();
}


auto media::source::media_source::get_handle() const -> media_source_handle*
{
    ACCESS_PIMPL(const media_source);
    return d->handle.get();
}


auto media::source::media_source::get_source_buffers() const -> ranges::any_helpful_view<source_buffer*>
{
    ACCESS_PIMPL(const media_source);
    return d->source_buffers | ranges::views::transform(&std::unique_ptr<source_buffer>::get);
}


auto media::source::media_source::get_active_source_buffers() const -> ranges::any_helpful_view<source_buffer*>
{
    ACCESS_PIMPL(const media_source);
    return d->active_source_buffers; // TODO : add a filter
}


auto media::source::media_source::get_ready_state() const -> detail::ready_state_t
{
    ACCESS_PIMPL(const media_source);
    return d->ready_state;
}


auto media::source::media_source::get_duration() const -> ext::number<double>
{
    ACCESS_PIMPL(const media_source);
    return d->ready_state == detail::ready_state_t::CLOSED ? ext::number<double>::nan() : d->duration;
}


auto media::source::media_source::set_duration(ext::number<double> new_duration) -> ext::number<double>
{
    ACCESS_PIMPL(media_source);
    using enum v8_primitive_error_t;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [new_duration] {return new_duration < 0 || ext::is_nan(new_duration);},
            u8"New duration value must be > 0 and not NaN");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->ready_state != detail::ready_state_t::OPEN;},
            u8"Ready state must be open");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return ranges::any_of(d->source_buffers, [](auto&& buffer) {return buffer->d_func()->updating == true;});},
            u8"No source buffers can be updating");

    detail::duration_change(this, new_duration);
}
