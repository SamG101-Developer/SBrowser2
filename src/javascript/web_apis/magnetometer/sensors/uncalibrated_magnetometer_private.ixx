module;
#include "ext/macros/pimpl.hpp"


export module apis.magnetometer.uncalibrated_magnetometer_private;
import apis.sensors.sensor_private;


DEFINE_PRIVATE_CLASS(magnetometer, uncalibrated_magnetometer)
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(uncalibrated_magnetometer);
};
