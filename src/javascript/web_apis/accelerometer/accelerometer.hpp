#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP

#include "sensors/sensor.hpp"
namespace accelerometer {class accelerometer;}

#include USE_INNER_TYPES(accelerometer)


class accelerometer::accelerometer
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(accelerometer);
    accelerometer() = default;
    accelerometer(detail::accelerometer_sensor_options_t&& options);

public js_properties:
    ext::property<ext::number<double>> x;
    ext::property<ext::number<double>> y;
    ext::property<ext::number<double>> z;

public cpp_members:
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(x);
    DEFINE_CUSTOM_GETTER(y);
    DEFINE_CUSTOM_GETTER(z);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
