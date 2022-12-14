module;
#include "ext/macros/pimpl.hpp"


export module apis.accelerometer.gravity_sensor_private;
import apis.accelerometer.accelerometer_private;


DEFINE_PRIVATE_CLASS(accelerometer, gravity_sensor) final
        : accelerometer_private
{
    MAKE_QIMPL(gravity_sensor);
};
