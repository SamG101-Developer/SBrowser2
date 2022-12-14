export module apis.accelerometer.types;

import ext.any;
import ext.map;
import ext.string;


export namespace accelerometer::detail
{
    using accelerometer_reading_values_t = ext::map<ext::string, ext::any>;

    enum class accelerometer_local_coordinate_system_t {DEVICE, SCREEN};
};
