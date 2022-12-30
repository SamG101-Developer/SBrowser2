module;
#include "ext/macros.hpp"


export module apis.gyroscope.gyroscope:p;
import apis.sensors.sensor;


DEFINE_PRIVATE_CLASS(gyroscope, gyroscope) : sensors::sensor_private {};
