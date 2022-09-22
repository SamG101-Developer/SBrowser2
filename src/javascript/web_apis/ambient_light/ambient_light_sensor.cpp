#include "ambient_light_sensor.hpp"

#include "ext/pimpl.hpp"

#include "ambient_light/detail/abstract_operations_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"


ambient_light_sensor::ambient_light_sensor::ambient_light_sensor(
        sensors::detail::sensor_options_t&& options)
        : INIT_PIMPL
{
    // Construct an AmbientLight instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_ambient_light_sensor_object(this, std::move(options));
}


auto ambient_light_sensor::ambient_light_sensor::get_illuminance()
        -> const ext::number<double>&
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
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<ambient_light_sensor>{isolate}
        .inherit<sensors::sensor>()
        .ctor<sensors::detail::sensor_options_t&&>()
        .property("illuminance", &ambient_light_sensor::get_illuminance)
        .auto_wrap_objects();

    return std::move(conversion);
}
