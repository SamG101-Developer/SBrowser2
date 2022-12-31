module;
#include "ext/macros.hpp"


export module apis.gamepad.gamepad_event;
import apis.dom.event;

IMPORT_ALL_TYPES(gamepad);


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
