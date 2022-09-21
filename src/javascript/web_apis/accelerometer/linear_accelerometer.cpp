#include "linear_accelerometer.hpp"

#include "accelerometer/detail/abstract_operations_internals.hpp"


accelerometer::linear_accelerometer::linear_accelerometer(
        detail::accelerometer_sensor_options_t&& options)
{
    // Construct a LinearAccelerometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}


auto accelerometer::linear_accelerometer::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<linear_accelerometer>{isolate}
        .ctor<detail::accelerometer_local_coordinate_system_t&&>()
        .inherit<accelerometer>()
        .auto_wrap_objects();

    return std::move(conversion);
}
