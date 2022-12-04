#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MEDIA_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MEDIA_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include "ext/number.ixx"
#include "ext/promise.ixx"
#include <qmediaplayer.h>
namespace html::basic_media {class abstract_track;}
namespace html::basic_media {class media_error;}
namespace html::basic_media {class text_track;}
namespace html::basic_media {class text_track_cue;}
namespace html::messaging {class message_channel;}
namespace html::messaging {class message_port;}


DEFINE_PRIVATE_CLASS(html::elements, html_media_element) : html::elements::html_element_private
{
    std::unique_ptr<basic_media::media_error> error;
    ext::string src;
    ext::string current_src;
    detail::cross_origin_settings_attribute_t cross_origin;
    ext::number<ushort> network_state;
    detail::preload_t preload;
    ext::number<ushort> ready_state;
    ext::boolean seeking;
    ext::boolean autoplay;
    ext::boolean loop;
    ext::boolean controls;
    ext::boolean muted;
    ext::vector<std::unique_ptr<basic_media::abstract_track>> tracks;
    auto paused() const {return media_resource->playbackState() & QMediaPlayer::PlaybackState::PausedState;}
    auto ended() const {return media_resource->mediaStatus() & QMediaPlayer::MediaStatus::EndOfMedia;}

    detail::origin_t origin;
    std::unique_ptr<detail::task_queue_t> media_element_event_task_source;
    detail::media_provider_t assigned_media_provider_object;
    ext::boolean can_autoplay_flag;
    ext::boolean delaying_load_event_flag;
    ext::number<double> current_playback_position;
    ext::number<double> official_playback_position;
    ext::number<double> default_playback_position;
    ext::boolean show_poster_flag;
    ext::vector<ext::promise<void>> pending_play_promises; // TODO <T>
    ext::vector<basic_media::text_track*> pending_text_tracks;
    ext::vector<basic_media::text_track_cue*> newly_introduced_cues; // TODO : unique-ptr?
    ext::boolean pending_track_change_notification_flag;
    ext::number<double> playback_volume;
    std::unique_ptr<QMediaPlayer> media_resource;
    
    /* [MEDIA-SOURCE] */
    std::unique_ptr<html::messaging::message_port> s_port_to_worker;
    std::unique_ptr<html::messaging::message_channel> s_channel_with_worker;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MEDIA_ELEMENT_PRIVATE_HPP
