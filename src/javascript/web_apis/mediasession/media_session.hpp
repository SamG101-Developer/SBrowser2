#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_SESSION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_SESSION_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace mediasession {class media_session;}
namespace mediasession {class media_session_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(mediasession)
namespace mediasession {class media_metadata;}


class mediasession::media_session
        : virtual public dom_object
{
public constructors:
    media_session();
    MAKE_PIMPL(media_session);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto set_action_handler(detail::media_session_action_t action, detail::media_session_action_handler_t&& handler) -> void;
    auto set_position_state(detail::media_position_state_t&& state = {}) -> void;
    auto set_microphone_active(ext::boolean active) -> void;
    auto set_camera_active(ext::boolean active) -> void;

public js_properties:
    DEFINE_GETTER(metadata, media_metadata*);
    DEFINE_GETTER(playback_state, detail::media_session_playback_state_t);

    DEFINE_SETTER(metadata, media_metadata*);
    DEFINE_SETTER(playback_state, detail::media_session_playback_state_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_SESSION_HPP
