#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP

#include "sensors/sensor.hpp"
namespace accelerometer {class accelerometer;}
namespace accelerometer {class accelerometer_private;}

#include INCLUDE_INNER_TYPES(accelerometer)


class accelerometer::accelerometer
        : public sensors::sensor
{
public constructors:
    accelerometer(detail::accelerometer_sensor_options_t&& options);
    DOM_CTORS(accelerometer);
    MAKE_PIMPL(accelerometer);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
