module;
#include "ext/macros.hpp"


export module apis.accelerometer.linear_acceleration_sensor:p;
import apis.accelerometer.accelerometer;


DEFINE_PRIVATE_CLASS(accelerometer, linear_acceleration_sensor) final
        : accelerometer_private
{
public:
    MAKE_QIMPL(linear_accelerometer);
};
