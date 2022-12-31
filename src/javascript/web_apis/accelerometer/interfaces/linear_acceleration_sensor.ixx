module;
#include "ext/macros.hpp"


export module apis.accelerometer.linear_acceleration_sensor;
import apis.accelerometer.accelerometer;


DEFINE_PUBLIC_CLASS(accelerometer, linear_acceleration_sensor) final
        : public accelerometer
{
public constructors:
    linear_acceleration_sensor(accelerometer_sensor_options_t&& options);
    DOM_CTORS(linear_acceleration_sensor);
    MAKE_PIMPL(linear_acceleration_sensor);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);
};
