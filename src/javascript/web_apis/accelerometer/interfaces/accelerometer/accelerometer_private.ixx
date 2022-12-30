module;
#include "ext/macros.hpp"


export module apis.accelerometer.accelerometer:p;
import apis.sensors.sensor;


DEFINE_PRIVATE_CLASS(accelerometer, accelerometer)
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(accelerometer);
};
