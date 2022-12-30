module;
#include "ext/macros.hpp"


export module apis.geolocation_sensor.geolocation_sensor;
import apis.sensors.sensor;

import ext.core;
import ext.js;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(geolocation_sensor, geolocation_sensor) final
        : public sensors::sensor
{
public typedefs:
    using geolocation_sensor_options_t = ext::map<ext::string, ext::any>;
    using geolocation_sensor_reading_t = ext::map<ext::string, ext::any>;
    using read_options_t = ext::map<ext::string, ext::any>;

public constructors:
    geolocation_sensor(geolocation_sensor_options_t&& options);
    DOM_CTORS(geolocation_sensor);
    MAKE_PIMPL(geolocation_sensor);
    MAKE_V8_AVAILABLE(DEDICATED_WORKER | WINDOW);

public js_methods:
    auto read(read_options_t&& read_options) -> ext::promise<geolocation_sensor_reading_t>;

private js_properties:
    DEFINE_GETTER(latitude, ext::number<double>);
    DEFINE_GETTER(longitude, ext::number<double>);
    DEFINE_GETTER(altitude, ext::number<double>);
    DEFINE_GETTER(accuracy, ext::number<double>);
    DEFINE_GETTER(altitude_accuracy, ext::number<double>);
    DEFINE_GETTER(heading, ext::number<double>);
    DEFINE_GETTER(speed, ext::number<double>);
};
