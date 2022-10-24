#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event_private.hpp"

#include INCLUDE_INNER_TYPES(mediacapture_handle)


DEFINE_PRIVATE_CLASS(mediacapture::handle, capture_action_event) : dom::events::event_private
{
    detail::capture_action_t action;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_PRIVATE_HPP
