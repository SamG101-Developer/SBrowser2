module;
#include "ext/macros.hpp"


export module apis.accelerometer.gravity_sensor:p;
import apis.accelerometer.accelerometer;


DEFINE_PRIVATE_CLASS(accelerometer, gravity_sensor) final
        : accelerometer_private
{
public:
    MAKE_QIMPL(gravity_sensor);
};
