#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_HPP


namespace mediacapture::handle {class capture_action_event;}
namespace mediacapture::handle {class capture_action_event_private;}

#include INCLUDE_INNER_TYPES(mediacapture_handle)


class mediacapture::handle::capture_action_event
        : public dom::events::event
{
public constructors:
    capture_action_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(capture_action_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(action, detail::capture_action_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE_CAPTURE_ACTION_EVENT_HPP
