module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.device_orientation.device_motion_event_rotation_rate;
import apis._.dom_object;

import ext.enums;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(device_orientation, device_motion_event_rotation_rate)
        : public dom_object
{
public constructors:
    device_motion_event_rotation_rate();
    MAKE_PIMPL(device_motion_event_rotation_rate);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_properties:
    DEFINE_GETTER(alpha, ext::number<double>);
    DEFINE_GETTER(beta , ext::number<double>);
    DEFINE_GETTER(gamma, ext::number<double>);
};
