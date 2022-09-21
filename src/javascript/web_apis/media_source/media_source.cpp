#include "media_source.hpp"
#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(media_source)

#include "dom/detail/event_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/window.hpp"

#include "html/basic_media/audio_track.hpp"
#include "html/basic_media/text_track.hpp"
#include "html/basic_media/time_ranges.hpp"
#include "html/basic_media/video_track.hpp"
#include "html/detail/task_internals.hpp"

#include "media_source/source_buffer.hpp"
#include "media_source/detail/algorithm_internals.hpp"

#include "mimesniff/detail/mimetype_internals.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/cache1.hpp>
#include <range/v3/to_container.hpp>


auto media::source::media_source::add_source_buffer(
        const ext::string& type)
        -> source_buffer
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&type] {return type.empty();},
            "Source buffer type can not be empty");

    dom::detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [&type] {return !mimesniff::detail::valid_mime_type(type);},
            "Source buffer type is an invalid mime-type");

    dom::detail::throw_v8_exception_formatted<QUOTA_EXCEEDED_ERR>(
            [&type] {return false; /* TODO */;},
            "");

    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [state = ready_state()] {return state != detail::ready_state_t::OPEN;},
            "State must be 'open'");

    auto source_buffer = media::source::source_buffer{};
    source_buffer.s_generate_timestamps_flag = mse::byte_stream_format_registry::registry(mimesniff::detail::parse_mime_type(type)).generate_timestamps_flag;
    source_buffer.mode = source_buffer.s_generate_timestamps_flag ? detail::append_mode_t::SEQUENCE : detail::append_mode_t::SEGMENTS;
    source_buffers().push_back(&source_buffer);

    dom::detail::queue_task(html::detail::dom_manipulation_task_source,
            [buffers = source_buffers()]
            {dom::detail::fire_event("addsourcebuffer", buffers);});

    return source_buffer;
}


auto media::source::media_source::remove_source_buffer(
        source_buffer* source_buffer)
        -> void
{
    dom::detail::throw_v8_exception_formatted<NOT_FOUND_ERR>(
            [source_buffer, buffers = source_buffers()] {return !ranges::contains(buffers, source_buffer);},
            "'source_buffer' not fouund in the 'buffers' list");

    if (source_buffer->updating())
    {
        // TODO: abort buffer_append() if its running
        source_buffer->updating = false;

        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [source_buffer] {dom::detail::fire_event("abort", source_buffer);});

        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [source_buffer] {dom::detail::fire_event("updateend", source_buffer);});
    }

    for (decltype(auto) audio_track: *source_buffer->audio_tracks())
    {
        JS_REALM_GET_CURRENT;
        audio_track->source_buffer = nullptr;
        *source_buffer->audio_tracks() |= ranges::actions::remove(audio_track);
        detail::mirror_if_necessary(
                v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object),
                [audio_track, &audio_tracks = *source_buffer->audio_tracks()]
                {audio_tracks |= ranges::actions::remove(audio_track);});
    }
    
    for (decltype(auto) video_track: *source_buffer->video_tracks())
    {
        JS_REALM_GET_CURRENT;
        video_track->source_buffer = nullptr;
        *source_buffer->video_tracks() |= ranges::actions::remove(video_track);
        detail::mirror_if_necessary(
                v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object),
                [video_track, &video_tracks = *source_buffer->video_tracks()]
                {video_tracks |= ranges::actions::remove(video_track);});
    }

    for (decltype(auto) text_track: *source_buffer->text_tracks())
    {
        JS_REALM_GET_CURRENT;
        text_track->source_buffer = nullptr;
        *source_buffer->text_tracks() |= ranges::actions::remove(text_track);
        detail::mirror_if_necessary(
                v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object),
                [text_track, &text_tracks = *source_buffer->text_tracks()]
                {text_tracks |= ranges::actions::remove(text_track);});
    }

    if (ranges::contains(active_source_buffers(), source_buffer))
    {
        active_source_buffers() |= ranges::actions::remove(source_buffer);
        dom::detail::queue_task(html::detail::dom_manipulation_task_source,
                [active_buffers = active_source_buffers()]
                {dom::detail::fire_event("removesourcebuffer", active_buffers);});
    }

    source_buffers() |= ranges::actions::remove(source_buffer);
    dom::detail::queue_task(html::detail::dom_manipulation_task_source,
            [active_buffers = source_buffers()]
            {dom::detail::fire_event("removesourcebuffer", active_buffers);});

    // TODO: Destroy all resources for sourceBuffer.
}


auto media::source::media_source::end_of_stream(
        ext::optional<detail::end_of_stream_error_t> error)
        -> void
{
    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [state = ready_state()] {return state != detail::ready_state_t::OPEN;},
            "State must be 'open'");

    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [buffers = source_buffers()] {return ranges::any_of(buffers | ranges::views::transform_to_attr(&source_buffer::updating), ext::bind_front{ext::cmp::eq{}, true})},
            "Cannot end a stream that contains updating buffers");

    detail::end_of_stream(this, error);
}


auto media::source::media_source::set_live_seekable_range(
        ext::number<double> start,
        ext::number<double> end)
        -> void
{
    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [state = ready_state()] {return state != detail::ready_state_t::OPEN;},
            "State must be 'open'");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&start, &end] {return start < 0 || start > end;},
            "'start' must be positive and less than 'end'");

    s_live_seekable_range = std::make_unique<html::basic_media::time_ranges>();
    s_live_seekable_range()->m_ranges.emplace_back(start, end);
}
