module;
#include "ext/macros.hpp"


export module apis.gamepad.gamepad_button;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(gamepad, gamepad_button) final
        : public virtual dom_object
{
public constructors:
    gamepad_button();
    MAKE_PIMPL(gamepad_button);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(pressed, ext::boolean);
    DEFINE_GETTER(touched, ext::boolean);
    DEFINE_GETTER(value, ext::number<double>);
};
