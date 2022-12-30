module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros.hpp"
#include "javascript/macros/expose.hpp"


export module apis.accelerometer.gravity_sensor;
import apis.accelerometer.accelerometer;

import ext.enums;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(accelerometer, gravity_sensor) final
        : public accelerometer
{
public constructors:
    gravity_sensor(accelerometer_sensor_options_t&& options);
    DOM_CTORS(gravity_sensor);
    MAKE_PIMPL(gravity_sensor);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);
};
