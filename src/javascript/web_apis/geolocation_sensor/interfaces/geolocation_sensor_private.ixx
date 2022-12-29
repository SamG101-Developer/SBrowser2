module;
#include "ext/macros/macros.hpp"


export module apis.geolocation_sensor.geolocation_sensor_private;
import apis.sensors.sensor_private;


DEFINE_PRIVATE_CLASS(geolocation_sensor, geolocation_sensor) : sensors::sensor_private {};
