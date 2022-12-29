module;
#include "ext/macros/macros.hpp"
#include <libgamepad.hpp>


export module apis.gamepad.gamepad_button_private;
import apis.dom_object_private;

import ext.core;


DEFINE_PRIVATE_CLASS(gamepad, gamepad_button)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(gamepad_button);

public:
    ext::boolean pressed = false;
    ext::boolean touched = false;
    ext::number<double> value = 0.0;
};
