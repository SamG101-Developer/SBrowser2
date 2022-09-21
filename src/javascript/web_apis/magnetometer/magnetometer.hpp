#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_MAGNETOMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_MAGNETOMETER_HPP

#include "sensors/sensor.hpp"
namespace magnetometer {class magnetometer;}

#include INCLUDE_INNER_TYPES(magnetometer)


class magnetometer::magnetometer
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(magnetometer);
    magnetometer(detail::magnetometer_sensor_options_t&& options = {});

public js_properties:
    ext::property<ext::number<double>> x;
    ext::property<ext::number<double>> y;
    ext::property<ext::number<double>> z;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(x);
    DEFINE_CUSTOM_GETTER(y);
    DEFINE_CUSTOM_GETTER(z);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_MAGNETOMETER_HPP
