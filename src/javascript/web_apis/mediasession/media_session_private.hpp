#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_SESSION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_SESSION_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(mediasession)
namespace mediasession {class media_metadata;}


DEFINE_PRIVATE_CLASS(mediasession, media_session)
        : virtual dom_object_private
{
    MAKE_QIMPL(media_session);

    ext::map<detail::media_session_action_t, detail::media_session_action_handler_t*> supported_media_session_actions;
    std::unique_ptr<media_metadata> metadata;

    detail::media_session_playback_state_t state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_SESSION_PRIVATE_HPP
