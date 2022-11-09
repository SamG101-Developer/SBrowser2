#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_MAGNETOMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_MAGNETOMETER_HPP

#include "sensors/sensor.hpp"
namespace magnetometer {class magnetometer;}
namespace magnetometer {class magnetometer_private;}

#include INCLUDE_INNER_TYPES(magnetometer)


class magnetometer::magnetometer
        : public sensors::sensor
{
public constructors:
    magnetometer(detail::magnetometer_sensor_options_t&& options);
    DOM_CTORS(magnetometer);
    MAKE_PIMPL(magnetometer);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_MAGNETOMETER_HPP
