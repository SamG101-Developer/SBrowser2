#include "linear_accelerometer.hpp"

#include "accelerometer/detail/abstract_operations_internals.hpp"


accelerometer::linear_accelerometer::linear_accelerometer(
        detail::accelerometer_sensor_options_t&& options)
{
    // Construct a LinearAccelerometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}
