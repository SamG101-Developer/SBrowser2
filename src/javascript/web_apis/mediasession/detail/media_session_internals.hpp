#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_DETAIL_MEDIA_SESSION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_DETAIL_MEDIA_SESSION_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(mediasession)
namespace mediasession {class media_metadata;}
namespace mediasession {class media_session;}


namespace mediasession::detail
{
    auto active_media_session()
            -> media_session*;

    auto update_metadata()
            -> void;

    auto fetch_image()
            -> void;

    auto update_action_handler(
            media_session* media_session,
            detail::media_session_action_t action,
            detail::media_session_action_handler_t&& handler)
            -> void;

    auto handle_media_session_actions()
            -> void;

    auto joint_command_play_pause()
            -> void;

    auto media_session_actions_update()
            -> void;

    auto actual_playback_rate()
            -> ext::number<double>;

    auto current_playback_position()
            -> ext::number<double>;

    auto empty_metadata(
            media_metadata* metadata)
            -> ext::boolean;

    auto convert_artwork(
            ext::vector<media_image_t>&& input)
            -> ext::vector<media_image_t>;
}


struct mediasession::detail::position_state_t
{
    ext::number<double> duration;
    ext::number<double> playback_rate;
    ext::number<double> last_reported_playback_position;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_DETAIL_MEDIA_SESSION_INTERNALS_HPP
