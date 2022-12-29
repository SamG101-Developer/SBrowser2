module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.device_posture.device_posture;
import apis.dom.event_target;
import apis.device_posture.types;

import ext.core;
import js.env.module_type;


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
