#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_GEOLOCATION_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_GEOLOCATION_SENSOR_HPP

#include "sensors/sensor.hpp"
namespace geolocation_sensor {class geolocation_sensor;}
namespace geolocation_sensor {class geolocation_sensor_private;}


#include INCLUDE_INNER_TYPES(geolocation_sensor)


class geolocation_sensor::geolocation_sensor
        : public sensors::sensor
{
public constructors:
    geolocation_sensor(detail::geolocation_sensor_options_t&& options);
    DOM_CTORS(geolocation_sensor);
    MAKE_PIMPL(geolocation_sensor);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto read(detail::read_options_t&& read_options) -> ext::promise<detail::geolocation_sensor_reading_t>;

private js_properties:
    DEFINE_GETTER(latitude, ext::number<double>);
    DEFINE_GETTER(longitude, ext::number<double>);
    DEFINE_GETTER(altitude, ext::number<double>);
    DEFINE_GETTER(accuracy, ext::number<double>);
    DEFINE_GETTER(altitude_accuracy, ext::number<double>);
    DEFINE_GETTER(heading, ext::number<double>);
    DEFINE_GETTER(speed, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_GEOLOCATION_SENSOR_HPP
