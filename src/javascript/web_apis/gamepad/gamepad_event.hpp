#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP

#include "dom/events/event.hpp"
namespace gamepad {class gamepad_event;}

namespace gamepad {class gamepad;}


class gamepad::gamepad_event
        : public dom::events::event
{
public constructors:
    gamepad_event() = default;
    gamepad_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<std::unique_ptr<gamepad>> gamepad;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_EVENT_HPP
