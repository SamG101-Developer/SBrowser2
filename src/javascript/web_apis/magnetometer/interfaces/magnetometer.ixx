module;
#include "ext/macros.hpp"


export module apis.magnetometer.magnetometer;
import apis.sensors.sensor;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(magnetometer, magnetometer) final
        : public sensors::sensor
{
public typedefs:
    using magnetometer_sensor_options_t = ext::map<ext::string, ext::any>;

public constructors:
    magnetometer(detail::magnetometer_sensor_options_t&& options);
    DOM_CTORS(magnetometer);
    MAKE_PIMPL(magnetometer);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};
