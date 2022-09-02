#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_HPP

#include "dom/events/event.hpp"
namespace mediacapture::handle {class capture_action_event;}

#include USE_INNER_TYPES(mediacapture_handle)


class mediacapture::handle::capture_action_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(capture_action_event);
    capture_action_event() = default;
    capture_action_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    detail::capture_action_t action;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_HPP
