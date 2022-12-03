#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/boolean.ixx"
#include "ext/number.ixx"


DEFINE_PRIVATE_CLASS(gamepad, gamepad_button): virtual dom_object_private
{
    ext::boolean pressed = false;
    ext::boolean touched = false;
    ext::number<double> value = 0.0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_PRIVATE_HPP
