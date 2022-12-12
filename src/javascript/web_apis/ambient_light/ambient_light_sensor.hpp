#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_HPP


namespace ambient_light_sensor {class ambient_light_sensor;}
namespace ambient_light_sensor {class ambient_light_sensor_private;}


class ambient_light_sensor::ambient_light_sensor
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


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_AMBIENT_LIGHT_SENSOR_HPP
