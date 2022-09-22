#include "accelerometer.hpp"

#include "accelerometer/detail/abstract_operations_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"
#include "sensors/sensor.hpp"


accelerometer::accelerometer::accelerometer(
        detail::accelerometer_sensor_options_t&& options)
        : INIT_PIMPL
{
    // Construct an Accelerometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}


auto accelerometer::accelerometer::get_x()
        -> const ext::number<double>&
{
    // Get the latest reading for the "x" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_x = sensors::detail::get_value_from_latest_reading(this, "x");
    auto defaulted_x = candidate_x.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_x = defaulted_x.at("x").to<ext::number<double>>();
    return extracted_x;
}


auto accelerometer::accelerometer::get_y()
        -> const ext::number<double>&
{
    // Get the latest reading for the "y" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_y = sensors::detail::get_value_from_latest_reading(this, "y");
    auto defaulted_y = candidate_y.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_y = defaulted_y.at("y").to<ext::number<double>>();
    return extracted_y;
}


auto accelerometer::accelerometer::get_z()
        -> const ext::number<double>&
{
    // Get the latest reading for the "z" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_z = sensors::detail::get_value_from_latest_reading(this, "z");
    auto defaulted_z = candidate_z.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_z = defaulted_z.at("z").to<ext::number<double>>();
    return extracted_z;
}


auto accelerometer::accelerometer::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<accelerometer>{isolate}
        .inherit<sensors::sensor>()
        .ctor<detail::accelerometer_sensor_options_t&&>()
        .property("x", &accelerometer::get_x)
        .property("y", &accelerometer::get_y)
        .property("z", &accelerometer::get_z)
        .auto_wrap_objects();

    return std::move(conversion);
}
