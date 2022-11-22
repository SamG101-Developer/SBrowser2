#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "sensors/sensor_private.hpp"


DEFINE_PRIVATE_CLASS(ambient_light_sensor, ambient_light_sensor)
        : sensors::sensor_private
{
    MAKE_QIMPL(ambient_light_sensor);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_PRIVATE_HPP
