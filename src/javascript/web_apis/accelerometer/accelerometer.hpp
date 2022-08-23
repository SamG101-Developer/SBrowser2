#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP

#include "sensors/sensor.hpp"
namespace accelerometer {class accelerometer;}

#include USE_INNER_TYPES(accelerometer)
#include USE_INNER_TYPES(sensors)


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

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<sensors::detail::sensor_type_t> m_sensor;

private cpp_accessors:
    DEFINE_GETTER(x);
    DEFINE_GETTER(y);
    DEFINE_GETTER(z);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_ACCELEROMETER_HPP
