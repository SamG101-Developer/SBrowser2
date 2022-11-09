#include "gyroscope.hpp"
#include "gyroscope_private.hpp"

#include "gyroscope/detail/abstract_operations_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"
#include "sensors/sensor.hpp"


gyroscope::gyroscope::gyroscope(
        detail::gyroscope_sensor_options_t&& options)
{
    // Construct an gyroscope instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_gyroscope_object(this, std::move(options));
}


auto gyroscope::gyroscope::get_x() const -> ext::number<double>
{
    // Get the latest reading for the "x" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_x = sensors::detail::get_value_from_latest_reading(this, u"x");
    auto defaulted_x = candidate_x.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_x = defaulted_x.at(u"x").to<ext::number<double>>();
    return extracted_x;
}


auto gyroscope::gyroscope::get_y() const -> ext::number<double>
{
    // Get the latest reading for the "y" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_y = sensors::detail::get_value_from_latest_reading(this, u"y");
    auto defaulted_y = candidate_y.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_y = defaulted_y.at(u"y").to<ext::number<double>>();
    return extracted_y;
}


auto gyroscope::gyroscope::get_z() const -> ext::number<double>
{
    // Get the latest reading for the "z" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_z = sensors::detail::get_value_from_latest_reading(this, u"z");
    auto defaulted_z = candidate_z.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_z = defaulted_z.at(u"z").to<ext::number<double>>();
    return extracted_z;
}


auto gyroscope::gyroscope::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<gyroscope>{isolate}
        .ctor<detail::gyroscope_sensor_options_t&&>()
        .inherit<sensors::sensor>()
        .property("x", &gyroscope::get_x)
        .property("y", &gyroscope::get_y)
        .property("z", &gyroscope::get_z)
        .auto_wrap_objects();

    return std::move(conversion);
}
