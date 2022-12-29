module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.gamepad.gamepad_event;
import apis.dom.event;

import apis.gamepad.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(gamepad, gamepad_event) final
        : public dom::event
{
public typedefs:
    using gamepad_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    gamepad_event(ext::string&& event_type, gamepad_event_init_t&& event_init = {});
    MAKE_PIMPL(gamepad_event);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(gamepad, gamepad*);
};
