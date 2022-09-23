#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_UNCALIBRATED_MAGNETOMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_UNCALIBRATED_MAGNETOMETER_HPP

#include "magnetometer/magnetometer.hpp"
namespace magnetometer {class uncalibrated_magnetometer;}

#include INCLUDE_INNER_TYPES(magnetometer)


class magnetometer::uncalibrated_magnetometer
        : public magnetometer::magnetometer
{
public constructors:
    DOM_CTORS(uncalibrated_magnetometer);
    uncalibrated_magnetometer(detail::magnetometer_sensor_options_t&& options = {});

private js_properties:
    ext::property<ext::number<double>> x_bias;
    ext::property<ext::number<double>> y_bias;
    ext::property<ext::number<double>> z_bias;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

public cpp_accessors:
    DEFINE_CUSTOM_GETTER(x_bias);
    DEFINE_CUSTOM_GETTER(y_bias);
    DEFINE_CUSTOM_GETTER(z_bias);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_UNCALIBRATED_MAGNETOMETER_HPP
