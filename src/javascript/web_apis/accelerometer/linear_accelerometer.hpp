#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_HPP

#include "accelerometer/accelerometer.hpp"
namespace accelerometer {class linear_accelerometer;}


class accelerometer::linear_accelerometer
        : public accelerometer
{
public constructors:
    DOM_CTORS(linear_accelerometer);
    linear_accelerometer() = default;
    linear_accelerometer(detail::accelerometer_sensor_options_t&& options);

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_HPP
