module;
#include "ext/macros/pimpl.hpp"


export module apis.accelerometer.types;

import ext.core;


DEFINE_FWD_DECL_NAMESPACE(accelerometer)
{
    class accelerometer;
    class gravity_sensor;
    class linear_acceleraor_sensor;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(accelerometer)
{
    using accelerometer_reading_values_t = ext::map<ext::string, ext::any>;
    using linear_acceleration_reading_values_t = accelerometer_reading_values_t;
    using gravity_reading_values_t = accelerometer_reading_values_t;

    enum class accelerometer_local_coordinate_system_t {DEVICE, SCREEN};
};
