#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_HPP

#include "accelerometer/accelerometer.hpp"
namespace accelerometer {class gravity_sensor;}


class accelerometer::gravity_sensor
        : public accelerometer
{
public constructors:
    DOM_CTORS(gravity_sensor);
    gravity_sensor() = default;
    gravity_sensor(detail::accelerometer_sensor_options_t&& options = {});
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_GRAVITY_SENSOR_HPP
