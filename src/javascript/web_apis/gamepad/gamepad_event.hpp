#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP


namespace gamepad {class gamepad_event;}
namespace gamepad {class gamepad_event_private;}

namespace gamepad {class gamepad;}


class gamepad::gamepad_event
        : public dom::events::event
{
public constructors:
    gamepad_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(gamepad_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(gamepad, gamepad*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP
