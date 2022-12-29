module;
#include "ext/macros/macros.hpp"


export module apis.ambient_light.ambient_light_sensor_private;
import apis.sensors.sensor_private;


DEFINE_PRIVATE_CLASS(ambient_light, ambient_light_sensor) final
        : sensors::sensor_private
{
public:
    MAKE_QIMPL(ambient_light_sensor);
};
