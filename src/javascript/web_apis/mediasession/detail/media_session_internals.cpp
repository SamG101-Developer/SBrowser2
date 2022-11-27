#include "media_session_internals.hpp"

#include "ext/pair.hpp"

#include "mediasession/media_session.hpp"
#include "mediasession/media_session_private.hpp"

#include <range/v3/action/push_back.hpp>
#include <range/v3/action/remove.hpp>


auto mediasession::detail::update_action_handler_algorithm(
        mediasession::media_session* media_session,
        detail::media_session_action_t action,
        mediasession::media_session_action_handler* handler)
        -> void
{
    media_session->d_func()->supported_media_session_actions |= !handler
            ? ranges::actions::remove(action)
            : ranges::actions::push_back(ext::make_pair(action, handler));

    media_session_actions_update_algorithm(media_session);
}
