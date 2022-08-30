#include "magnetometer.hpp"

#include "sensors/detail/sensor_internals.hpp"


magnetometer::magnetometer::magnetometer(
        detail::magnetometer_sensor_options_t&& options)
{
    // Construct a Magnetometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_magnetometer_object(this, std::move(options));
}


auto magnetometer::magnetometer::get_x()
        const -> decltype(this->x)::value_t
{
    // Get the latest reading for the "x" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_x = sensors::detail::get_value_from_latest_reading(this, "x");
    auto defaulted_x = candidate_x.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_x = defaulted_x.at("x").to<ext::number<double>>();
    return extracted_x;
}


auto magnetometer::magnetometer::get_y()
        const -> decltype(this->y)::value_t
{
    // Get the latest reading for the "y" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_y = sensors::detail::get_value_from_latest_reading(this, "y");
    auto defaulted_y = candidate_y.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_y = defaulted_y.at("y").to<ext::number<double>>();
    return extracted_y;
}


auto magnetometer::magnetometer::get_z()
        const -> decltype(this->z)::value_t
{
    // Get the latest reading for the "z" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_z = sensors::detail::get_value_from_latest_reading(this, "z");
    auto defaulted_z = candidate_z.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_z = defaulted_z.at("z").to<ext::number<double>>();
    return extracted_z;
}
