module;
#include "ext/macros.hpp"


export module apis.geolocation_sensor.geolocation_sensor:p;
import apis.sensors.sensor;


DEFINE_PRIVATE_CLASS(geolocation_sensor, geolocation_sensor) : sensors::sensor_private {};
