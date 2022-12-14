export module apis.accelerometer.detail;


import apis.accelerometer.types;

namespace accelerometer {class accelerometer;}


namespace accelerometer::detail
{
    auto construct_accelerometer_object(
            accelerometer* sensor,
            accelerometer_sensor_options_t&& options)
            -> void;
}
