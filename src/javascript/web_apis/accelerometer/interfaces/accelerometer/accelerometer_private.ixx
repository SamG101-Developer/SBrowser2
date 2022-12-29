module;
#include "ext/macros/macros.hpp"


export module apis.accelerometer.accelerometer_private;
import apis.sensors.sensor_private;


DEFINE_PRIVATE_CLASS(accelerometer, accelerometer)
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(accelerometer);
};
