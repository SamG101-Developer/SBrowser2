#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP

#include "sensors/sensor.hpp"
namespace accelerometer {class accelerometer;}

#include INCLUDE_INNER_TYPES(accelerometer)

#include "accelerometer/accelerometer_private.hpp"


class accelerometer::accelerometer
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(accelerometer);
    accelerometer(detail::accelerometer_sensor_options_t&& options = {});
    MAKE_PIMPL(accelerometer);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
