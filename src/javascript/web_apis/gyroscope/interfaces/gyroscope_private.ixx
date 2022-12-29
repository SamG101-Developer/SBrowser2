module;
#include "ext/macros/pimpl.hpp"


export module apis.gyroscope.gyroscope_private;
import apis.sensors.sensor_private;


DEFINE_PRIVATE_CLASS(gyroscope, gyroscope) : sensors::sensor_private {};
