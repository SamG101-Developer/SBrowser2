module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.accelerometer.accelerometer;
import apis.sensors.sensor;

import ext.any;
import ext.enums;
import ext.number;
import ext.map;
import ext.string;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(accelerometer, accelerometer)
        : public sensors::sensor
{
public typedefs:
    using accelerometer_sensor_options_t = ext::map<ext::string, ext::any>;

public constructors:
    accelerometer(accelerometer_sensor_options_t&& options);
    DOM_CTORS(accelerometer);
    MAKE_PIMPL(accelerometer);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};
