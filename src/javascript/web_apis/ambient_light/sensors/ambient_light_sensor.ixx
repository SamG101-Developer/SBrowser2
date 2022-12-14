module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.ambient_light.ambient_light_sensor;
import apis.sensors.sensor;

import apis.sensors.types;
import ext.enums;
import ext.number;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(ambient_light_sensor, ambient_light_sensor) final
        : public sensors::sensor
{
public constructors:
    ambient_light_sensor(sensors::detail::sensor_options_t&& options = {});
    DOM_CTORS(ambient_light_sensor);
    MAKE_PIMPL(ambient_light_sensor);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(illuminance, ext::number<double>);
};
