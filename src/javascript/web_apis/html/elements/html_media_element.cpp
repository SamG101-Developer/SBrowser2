#include "html_media_element.hpp"
#include "html_media_element_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "html/basic_media/time_ranges.hpp"
#include "html/basic_media/time_ranges_private.hpp"


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
    ACCESS_PIMPL(const html_media_element);
    return d->network_state;
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
    ACCESS_PIMPL(const html_media_element);
    return d->autoplay;
}


auto html::elements::html_media_element::get_loop() const -> ext::boolean
{
    ACCESS_PIMPL(const html_media_element);
    return d->loop; // TODO : d->media-resource()->loops() > 0 ?
}


auto html::elements::html_media_element::get_controls() const -> ext::boolean
{
    ACCESS_PIMPL(const html_media_element);
    return d->controls;
}


auto html::elements::html_media_element::get_volume() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_media_element);
    return d->playback_volume;
}
