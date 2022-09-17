#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_GEOLOCATION_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_GEOLOCATION_SENSOR_HPP

#include "sensors/sensor.hpp"
#include "geolocation/geolocation_coordinates.hpp"
namespace geolocation_sensor {class geolocation_sensor;}


#include "ext/promise.hpp"
#include USE_INNER_TYPES(geolocation_sensor)


class geolocation_sensor::geolocation_sensor
        : public sensors::sensor
        , public geolocation::geolocation_coordinates
{
public constructors:
    DOM_CTORS(geolocation_sensor);
    geolocation_sensor(detail::geolocation_sensor_options_t&& options = {});

public js_methods:
    auto read(detail::read_options_t&& read_options) -> ext::promise<detail::geolocation_sensor_reading_t>;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(latitude);
    DEFINE_CUSTOM_GETTER(longitude);
    DEFINE_CUSTOM_GETTER(altitude);
    DEFINE_CUSTOM_GETTER(accuracy);
    DEFINE_CUSTOM_GETTER(altitude_accuracy);
    DEFINE_CUSTOM_GETTER(heading);
    DEFINE_CUSTOM_GETTER(speed);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_GEOLOCATION_SENSOR_HPP
