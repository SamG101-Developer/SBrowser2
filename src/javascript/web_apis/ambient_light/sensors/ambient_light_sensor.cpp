module;
#include "ext/macros/pimpl.hpp"


module apis.ambient_light.ambient_light_sensor;
import apis.ambient_light.ambient_light_sensor_private;

import apis.sensors.types;


ambient_light_sensor::ambient_light_sensor::ambient_light_sensor(sensors::detail::sensor_options_t&& options)
{
    INIT_PIMPL;

    // Construct an AmbientLight instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_ambient_light_sensor_object(this, std::move(options));
}


auto ambient_light_sensor::ambient_light_sensor::get_illuminance() const -> ext::number<double>
{
    // Get the latest reading for the "illuminance" value, default it to 0..0 if it doesn't exist, and then convert it
    // from the ext::any type to a double. Return the double.
    auto candidate_illuminance = sensors::detail::get_value_from_latest_reading(this, u"illuminance");
    auto defaulted_illuminance = candidate_illuminance.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_illuminance = defaulted_illuminance[u"illuminance"].to<ext::number<double>>();
    return extracted_illuminance;
}


auto ambient_light_sensor::ambient_light_sensor::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<sensors::sensor>()
        .ctor<sensors::detail::sensor_options_t&&>()
        .property("illuminance", &ambient_light_sensor::get_illuminance)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
