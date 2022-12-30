module;
#include "ext/macros.hpp"


export module apis.gamepad.gamepad_event:p;
import apis.dom.event;

import ext.core;


DEFINE_PRIVATE_CLASS(gamepad, gamepad_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(gamepad);

public:
    std::observer_ptr<gamepad> gamepad;
};
