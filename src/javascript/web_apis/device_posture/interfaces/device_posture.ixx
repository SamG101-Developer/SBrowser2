module;
#include "ext/macros.hpp"


export module apis.device_posture.device_posture;
import apis.dom.event_target;

IMPORT_ALL_TYPES(device_posture);


DEFINE_PUBLIC_CLASS(device_posture, device_posture) final
        : public dom::event_target
{
public constructors:
    DOM_CTORS(device_posture);
    MAKE_PIMPL(device_posture);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(type, detail::device_posture_type_t);
};
