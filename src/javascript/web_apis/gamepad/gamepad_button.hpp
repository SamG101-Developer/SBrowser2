#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_HPP

#include "dom_object.hpp"
namespace gamepad {class gamepad_button;}

#include "gamepad_button_private.hpp"


class gamepad::gamepad_button
        : public virtual dom_object
{
public constructors:
    gamepad_button();
    MAKE_PIMPL(gamepad_button);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(pressed, ext::boolean);
    DEFINE_GETTER(touched, ext::boolean);
    DEFINE_GETTER(value, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_HPP
