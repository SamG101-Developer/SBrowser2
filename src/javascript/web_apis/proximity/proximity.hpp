#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_PROXIMITY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_PROXIMITY_HPP

#include "sensors/sensor.hpp"
namespace proximity {class proximity;}

#include USE_INNER_TYPES(proximity)


class proximity::proximity
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(proximity);
    proximity(detail::proximity_sensor_options_t&& options = {});

public js_properties:
    ext::property<ext::number<double>> distance;
    ext::property<ext::number<double>> max;
    ext::property<ext::boolean> near;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(distance);
    DEFINE_CUSTOM_GETTER(max);
    DEFINE_CUSTOM_GETTER(near);
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_PROXIMITY_HPP
