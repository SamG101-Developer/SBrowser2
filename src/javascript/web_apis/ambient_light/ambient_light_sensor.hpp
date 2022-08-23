#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_HPP

#include "sensors/sensor.hpp"
namespace ambient_light_sensor {class ambient_light_sensor;}

class ambient_light_sensor::ambient_light_sensor
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(ambient_light_sensor);
    ambient_light_sensor() = default;
    ambient_light_sensor(sensors::detail::sensor_options_t&& options);

public js_properties:
    ext::property<ext::number<double>> illuminance;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_HPP
