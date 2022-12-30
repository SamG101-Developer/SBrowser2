module;
#include "ext/macros.hpp"


export module apis.magnetometer.magnetometer:p;
import apis.sensors.sensor;


DEFINE_PRIVATE_CLASS(magnetometer, magnetometer)
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(magnetometer);
};
