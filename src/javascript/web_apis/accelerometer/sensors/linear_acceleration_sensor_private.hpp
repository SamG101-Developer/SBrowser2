module;
#include "ext/macros/pimpl.hpp"


export module apis.accelerometer.linear_acceleration_sensor_private;
import apis.accelerometer.accelerometer;


DEFINE_PRIVATE_CLASS(accelerometer, linear_acceleration_sensor) final
        : accelerometer_private
{
    MAKE_QIMPL(linear_accelerometer);
};
