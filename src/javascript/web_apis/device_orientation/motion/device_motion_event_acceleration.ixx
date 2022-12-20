module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.device_orientation.device_motion_event_acceleration;
import apis.dom_object;

import ext.enums;
import ext.number;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(device_orientation, device_motion_event_acceleration)
        : public dom_object
{
public constructors:
    device_motion_event_acceleration();
    MAKE_PIMPL(device_motion_event_acceleration);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};
