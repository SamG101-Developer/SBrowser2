#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_GYROSCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_GYROSCOPE_HPP

#include "sensors/sensor.hpp"
namespace gyroscope {class gyroscope;};

#include INCLUDE_INNER_TYPES(gyroscope)


class gyroscope::gyroscope
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(gyroscope);
    gyroscope(detail::gyroscope_sensor_options_t&& sensor_options);

public js_properties:
    ext::property<ext::number<double>> x;
    ext::property<ext::number<double>> y;
    ext::property<ext::number<double>> z;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(x);
    DEFINE_CUSTOM_GETTER(y);
    DEFINE_CUSTOM_GETTER(z);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_GYROSCOPE_HPP
