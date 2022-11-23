#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_HPP

#include "accelerometer/accelerometer.hpp"
namespace accelerometer {class gravity_sensor;}
namespace accelerometer {class gravity_sensor_private;}


class accelerometer::gravity_sensor
        : public accelerometer
{
public constructors:
    gravity_sensor(detail::accelerometer_sensor_options_t&& options);
    DOM_CTORS(gravity_sensor);
    MAKE_PIMPL(gravity_sensor);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_HPP
