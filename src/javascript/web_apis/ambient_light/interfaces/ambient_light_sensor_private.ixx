module;
#include "ext/macros.hpp"


export module apis.ambient_light.ambient_light_sensor:p;
import apis.sensors.sensor;


DEFINE_PRIVATE_CLASS(ambient_light, ambient_light_sensor) final
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(ambient_light_sensor);
};
