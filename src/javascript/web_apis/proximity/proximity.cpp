#include "proximity.hpp"

#include "sensors/detail/sensor_internals.hpp"


auto proximity::proximity::get_distance() const -> ext::number<double>
{
    // Get the latest reading for the "distance" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_distance = sensors::detail::get_value_from_latest_reading(this, u8"distance");
    auto defaulted_distance = candidate_distance.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_distance = defaulted_distance.at(u8"distance").to<ext::number<double>>();
    return extracted_distance;
}


auto proximity::proximity::get_max() const -> ext::number<double>
{
    // Get the latest reading for the "max" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_max = sensors::detail::get_value_from_latest_reading(this, u8"max");
    auto defaulted_max = candidate_max.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_max = defaulted_max.at(u8"max").to<ext::number<double>>();
    return extracted_max;
}


auto proximity::proximity::get_near() const -> ext::boolean
{
    // Get the latest reading for the "near" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_near = sensors::detail::get_value_from_latest_reading(this, u8"near");
    auto defaulted_near = candidate_near.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_near = defaulted_near.at(u8"near").to<ext::boolean>();
    return extracted_near;
}
