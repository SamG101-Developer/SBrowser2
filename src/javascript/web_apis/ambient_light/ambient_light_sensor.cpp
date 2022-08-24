#include "ambient_light_sensor.hpp"

#include "ambient_light/detail/abstract_operations_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"


ambient_light_sensor::ambient_light_sensor::ambient_light_sensor(
        sensors::detail::sensor_options_t&& options)
        : illuminance{0.0}
{
    detail::construct_ambient_light_sensor_object(this, std::move(options));
}


auto ambient_light_sensor::ambient_light_sensor::get_illuminance()
        const -> decltype(this->illuminance)::value_t
{
    // Get the latest reading for the "illuminance" value, default it to 0..0 if it doesn't exist, and then convert it
    // from the ext::any type to a double. Return the double.
    auto candidate_illuminance = sensors::detail::get_value_from_latest_reading(this, "illuminance");
    auto defaulted_illuminance = candidate_illuminance.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_illuminance = defaulted_illuminance.at("illuminance").to<ext::number<double>>();
    return extracted_illuminance;
}


auto ambient_light_sensor::ambient_light_sensor::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<ambient_light_sensor>{isolate}
        .ctor<sensors::detail::sensor_options_t&&>()
        .inherit<sensors::sensor>()
        .var("illuminance", &ambient_light_sensor::illuminance, true)
        .auto_wrap_objects();
}
