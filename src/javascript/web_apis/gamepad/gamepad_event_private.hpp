#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event_private.hpp"

#include "ext/memory.hpp"
namespace gamepad {class gamepad;}


DEFINE_PRIVATE_CLASS(gamepad, gamepad_event) : dom::events::event_private
{
    std::observer_ptr<gamepad> gamepad = nullptr;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_PRIVATE_HPP
