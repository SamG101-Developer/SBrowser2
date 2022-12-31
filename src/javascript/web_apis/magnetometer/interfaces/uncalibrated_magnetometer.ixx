module;
#include "ext/macros.hpp"


export module apis.magnetometer.uncalibrated_magnetometer;
import apis.sensors.sensor;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(magnetometer, uncalibrated_magnetometer) final
        : public sensors::sensor
{
public typedefs:
    using uncalibrated_magnetometer_sensor_options_t = ext::map<ext::string, ext::any>;

public constructors:
    uncalibrated_magnetometer(uncalibrated_magnetometer_sensor_options_t&& options);
    DOM_CTORS(uncalibrated_magnetometer);
    MAKE_PIMPL(uncalibrated_magnetometer);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_properties:
    DEFINE_GETTER(x_bias, ext::number<double>);
    DEFINE_GETTER(y_bias, ext::number<double>);
    DEFINE_GETTER(z_bias, ext::number<double>);
};
