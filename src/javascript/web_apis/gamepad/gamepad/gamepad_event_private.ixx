module;
#include "ext/macros/pimpl.hpp"


export module apis.gamepad.gamepad_event_private;
import apis.dom.event_private;

import ext.core;


DEFINE_PRIVATE_CLASS(gamepad, gamepad_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(gamepad);

public:
    std::observer_ptr<gamepad> gamepad;
};
