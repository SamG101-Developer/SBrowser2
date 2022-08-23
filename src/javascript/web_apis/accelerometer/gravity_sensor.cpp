#include "gravity_sensor.hpp"

#include "accelerometer/detail/abstract_operations_internals.hpp"


accelerometer::gravity_sensor::gravity_sensor(
        detail::accelerometer_sensor_options_t&& options)
{
    // Construct aa GravitySensor instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}
