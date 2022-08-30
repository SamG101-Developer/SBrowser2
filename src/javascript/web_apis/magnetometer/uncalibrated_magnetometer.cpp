#include "uncalibrated_magnetometer.hpp"

#include "sensors/detail/sensor_internals.hpp"


magnetometer::uncalibrated_magnetometer::uncalibrated_magnetometer(
        detail::magnetometer_sensor_options_t&& options)
{
    // Construct a Magnetometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_magnetometer_object(this, std::move(options));
}


auto magnetometer::uncalibrated_magnetometer::get_x_bias()
        const -> decltype(this->x)::value_t
{
    // Get the latest reading for the "x" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_x_bias = sensors::detail::get_value_from_latest_reading(this, "xBias");
    auto defaulted_x_bias = candidate_x_bias.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_x_bias = defaulted_x_bias.at("xBias").to<ext::number<double>>();
    return extracted_x_bias;
}


auto magnetometer::uncalibrated_magnetometer::get_y_bias()
        const -> decltype(this->y)::value_t
{
    // Get the latest reading for the "y" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_y_bias = sensors::detail::get_value_from_latest_reading(this, "yBias");
    auto defaulted_y_bias = candidate_y_bias.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_y_bias = defaulted_y_bias.at("yBias").to<ext::number<double>>();
    return extracted_y_bias;
}


auto magnetometer::uncalibrated_magnetometer::get_z_bias()
        const -> decltype(this->z)::value_t
{
    // Get the latest reading for the "z" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_z_bias = sensors::detail::get_value_from_latest_reading(this, "zBias");
    auto defaulted_z_bias = candidate_z_bias.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_z_bias = defaulted_z_bias.at("z").to<ext::number<double>>();
    return extracted_z_bias;
}
