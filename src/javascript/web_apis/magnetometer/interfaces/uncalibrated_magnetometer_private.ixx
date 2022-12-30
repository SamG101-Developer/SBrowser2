module;
#include "ext/macros.hpp"


export module apis.magnetometer.uncalibrated_magnetometer:p;
import apis.sensors.sensor;


DEFINE_PRIVATE_CLASS(magnetometer, uncalibrated_magnetometer)
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(uncalibrated_magnetometer);
};
