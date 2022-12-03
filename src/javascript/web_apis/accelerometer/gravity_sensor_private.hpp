#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "accelerometer/accelerometer_private.hpp"


DEFINE_PRIVATE_CLASS(accelerometer, gravity_sensor)
        : accelerometer_private
{
    MAKE_QIMPL(gravity_sensor);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_PRIVATE_HPP
