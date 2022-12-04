#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION__TYPEDEFS_HPP





#include "ext/string.hpp"


namespace mediasession::detail
{
    struct media_session_action_source_t;
    struct position_state_t;

    enum class media_session_playback_state_t {NONE, PAUSED, PLAYING};
    enum class media_session_action_t {PLAY, PAUSE, SEEKBACKWARD, SEEKFORWARD, PREVIOUSTRACK, NEXTTRACK, SKIPAD, ATOP, SEEKTO, TOGGLEMICROPHONE, TOGGLECAMERA, HANGUP};

    using media_session_action_details_t = ext::map<ext::string, ext::any>;
    using media_position_state_t = ext::map<ext::string, ext::number<double>>;
    using media_metadata_init_t = ext::map<ext::string, ext::any>;
    using media_image_t = ext::map<ext::string, ext::any>;
    using media_session_action_handler_t = ext::function<void(media_session_action_details_t&& details)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION__TYPEDEFS_HPP
