#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"


namespace accelerometer::detail
{
    using accelerometer_sensor_options_t = ext::map<ext::string, ext::any>;
    using accelerometer_reading_values_t = ext::map<ext::string, ext::any>;
    using linear_accelerometer_reading_values_t = accelerometer_reading_values_t;
    using gravity_reading_values_t = accelerometer_reading_values_t;

    enum class accelerometer_local_coordinate_system_t {DEVICE, SCREEN};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER__TYPEDEFS_HPP
