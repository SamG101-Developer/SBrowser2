#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_HPP

#include "accelerometer/accelerometer.hpp"
namespace accelerometer {class linear_accelerometer;}
namespace accelerometer {class linear_accelerometer_private;}


class accelerometer::linear_accelerometer
        : public accelerometer
{
public constructors:
    linear_accelerometer(detail::accelerometer_sensor_options_t&& options);
    DOM_CTORS(linear_accelerometer);
    MAKE_PIMPL(linear_accelerometer);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_HPP
