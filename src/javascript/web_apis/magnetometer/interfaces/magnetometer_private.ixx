module;
#include "ext/macros/pimpl.hpp"


export module apis.magnetometer.magnetometer_private;
import apis.sensors.sensor_private;


DEFINE_PRIVATE_CLASS(magnetometer, magnetometer)
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(magnetometer);
};
