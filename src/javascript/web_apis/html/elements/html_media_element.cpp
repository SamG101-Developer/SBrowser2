#include "html_media_element.hpp"
#include "html_media_element_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/_typedefs.hpp"
#include "html/detail/media_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "html/basic_media/media_error.hpp"
#include "html/basic_media/media_error_private.hpp"
#include "html/basic_media/text_track.hpp"
#include "html/basic_media/text_track_private.hpp"
#include "html/basic_media/time_ranges.hpp"
#include "html/basic_media/time_ranges_private.hpp"
#include "html/events/track_event.hpp"

#include "media_source/media_source.hpp"
#include "media_source/detail/algorithm_internals.hpp"


auto html::elements::html_media_element::load() -> void
{
    return detail::media_element_load_algorithm(this);
}


auto html::elements::html_media_element::fast_seek(ext::number<double> time) -> void
{
    detail::seek(this, time, true);
}


auto html::elements::html_media_element::play() -> ext::promise<void>&
{
    ACCESS_PIMPL(html_media_element);
    using enum dom::detail::dom_exception_error_t;
    using enum detail::media_error_type_t;

    dom::detail::throw_v8_exception<NOT_ALLOWED_ERR>(
            [this] {!detail::is_allowed_to_play(this);},
            u8"Not allowed to play media");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->error && d->error->d_func()->code == MEDIA_ERR_SRC_NOT_SUPPORTED;},
            u8"Media not supported");

    d->pending_play_promises.emplace_back();
    detail::internal_play_steps(this);
    return d->pending_play_promises.back();
}


auto html::elements::html_media_element::pause() -> void
{
    ACCESS_PIMPL(html_media_element);
    if (d->network_state == NETWORK_EMPTY)
        detail::resource_selection_algorithm(this);
    detail::internal_pause_steps(this);
}


auto html::elements::html_media_element::add_text_track(
        detail::text_track_kind_t kind,
        ext::string&& label,
        ext::string&& language)
        -> basic_media::text_track*
{
    ACCESS_PIMPL(html_media_element);

    auto track = std::make_unique<basic_media::text_track>();
    track->d_func()->kind = kind;
    track->d_func()->label = std::move(label);
    track->d_func()->language = std::move(language);
    track->d_func()->readiness_state = detail::track_readiness_state_t::LOADED;
    track->d_func()->mode = detail::track_mode_t::HIDDEN;
    track->d_func()->text_track_cues = {};

    d->tracks.emplace_back(std::move(track));
    decltype(auto) raw_track = dynamic_cast<basic_media::text_track*>(d->tracks.back().get());

    dom::detail::queue_media_element_task(this,
            BIND_FRONT(dom::detail::fire_event<events::track_event>, u"addtrack", d->tracks, {{u"track", raw_track}}));

    return raw_track;
}


auto html::elements::html_media_element::get_error() const -> basic_media::media_error*
{
    ACCESS_PIMPL(const html_media_element);
    return d->error.get();
}


auto html::elements::html_media_element::get_src() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->src;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_src_object() const -> detail::media_provider_t
{
    ACCESS_PIMPL(const html_media_element);
    return d->assigned_media_provider_object;
}


auto html::elements::html_media_element::get_current_src() const -> ext::string_view
{
    ACCESS_PIMPL(const html_media_element);
    return d->current_src;
}


auto html::elements::html_media_element::get_cross_origin() const -> detail::cross_origin_settings_attribute_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->cross_origin;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_network_state() const -> ext::number<ushort>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->network_state;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_preload() const -> detail::preload_t
{
    ACCESS_PIMPL(const html_media_element);
    return d->preload;
}


auto html::elements::html_media_element::get_ready_state() const -> ext::number<ushort>
{
    ACCESS_PIMPL(const html_media_element);
    return d->ready_state;
}


auto html::elements::html_media_element::get_seeking() const -> ext::boolean
{
    ACCESS_PIMPL(const html_media_element);
    return d->seeking;
}


auto html::elements::html_media_element::get_current_time() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_media_element);
    return d->default_playback_position ?: d->official_playback_position;
}


auto html::elements::html_media_element::get_duration() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_media_element);
    return d->media_resource->duration();
}


auto html::elements::html_media_element::get_paused() const -> ext::boolean
{
    ACCESS_PIMPL(const html_media_element);
    return d->paused();
}


auto html::elements::html_media_element::get_default_playback_rate() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_media_element);
    return d->media_resource->playbackRate(); // TODO : this accounts for FF/RW but shouldn't
}


auto html::elements::html_media_element::get_playback_rate() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_media_element);
    return d->media_resource->playbackRate();
}


auto html::elements::html_media_element::get_played() const -> basic_media::time_ranges
{
    ACCESS_PIMPL(const html_media_element);
    auto time_ranges = html::basic_media::time_ranges{};
    time_ranges.d_func()->linked_vector->emplace_back(0.0, d->current_playback_position);
    return time_ranges;
}


auto html::elements::html_media_element::get_seekable() const -> basic_media::time_ranges
{
    ACCESS_PIMPL(const html_media_element);
    auto time_ranges = html::basic_media::time_ranges{};
    time_ranges.d_func()->linked_vector->emplace_back(0.0, d->media_resource->duration()); // TOOD : not correct
    return time_ranges;
}


auto html::elements::html_media_element::get_ended() const -> ext::boolean
{
    ACCESS_PIMPL(const html_media_element);
    return d->ended() && d->media_resource->playbackRate() > 0;
}


auto html::elements::html_media_element::get_autoplay() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->autoplay;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_loop() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->loop; // TODO : d->media-resource()->loops() > 0 ?
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_controls() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->controls;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_volume() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_media_element);
    return d->playback_volume;
}


auto html::elements::html_media_element::get_muted() const -> ext::boolean
{
    ACCESS_PIMPL(const html_media_element);
    return d->muted;
}


auto html::elements::html_media_element::get_default_muted() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->muted;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_audio_tracks() const -> ranges::any_helpful_view<basic_media::audio_track*>
{
    ACCESS_PIMPL(const html_media_element);
    return d->tracks
            | ranges::views::transform(&std::unique_ptr<basic_media::abstract_track>::get)
            | ranges::views::cast_all_to<basic_media::audio_track*>();
}


auto html::elements::html_media_element::get_video_tracks() const -> ranges::any_helpful_view<basic_media::video_track*>
{
    ACCESS_PIMPL(const html_media_element);
    return d->tracks
            | ranges::views::transform(&std::unique_ptr<basic_media::abstract_track>::get)
            | ranges::views::cast_all_to<basic_media::video_track*>();
}


auto html::elements::html_media_element::get_text_tracks() const -> ranges::any_helpful_view<basic_media::text_track*>
{
    ACCESS_PIMPL(const html_media_element);
    return d->tracks
            | ranges::views::transform(&std::unique_ptr<basic_media::abstract_track>::get)
            | ranges::views::cast_all_to<basic_media::text_track*>();
}


auto html::elements::html_media_element::set_src(ext::string new_src) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_media_element);
        return d->src = std::move(new_src);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::set_src_object(detail::media_provider_t new_src_object) -> detail::media_provider_t
{
    ACCESS_PIMPL(html_media_element);
    return d->assigned_media_provider_object = std::move(new_src_object);
}


auto html::elements::html_media_element::set_cross_origin(detail::cross_origin_settings_attribute_t new_cross_origin) -> detail::cross_origin_settings_attribute_t
{
    ACCESS_PIMPL(html_media_element);
    return d->cross_origin = new_cross_origin;
}


auto html::elements::html_media_element::set_preload(detail::preload_t new_preload) -> detail::preload_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_media_element);
        return d->preload = new_preload;
    CE_REACTIONS_METHOD_EXE
}
