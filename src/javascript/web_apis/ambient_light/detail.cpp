module;
#include "ext/macros/language_shorthand.hpp"


module apis.ambient_light.detail;
import apis.ambient_light.ambient_light_sensor;
import apis.ambient_light.ambient_light_sensor_private;

import apis.dom.detail;
import apis.dom.types;

import apis.sensors.detail;
import apis.sensors.types;

import ext.boolean;


auto ambient_light::detail::construct_ambient_light_sensor_object(
        ambient_light_sensor* sensor,
        sensors::detail::sensor_options_t&& options)
        -> void
{
    using enum dom::detail::dom_exception_error_t;

    // If the sensor isn't allowed by a policy, then throw a SecurityError, letting the user know that using this sensor
    // isn't permitted.
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [sensor] {return !sensors::detail::check_sensor_policy_controlled_features(*sensor->d_func()->sensor);},
            u8"AmbientLightSensor cannot be created due to a failed check in the sensor policy controlled features");

    // Initialize the sensor object, and set the coordinate system of the sensor
    sensors::detail::initialize_sensor_object(sensor, std::move(options));
}


auto ambient_light::detail::ambient_light_threshold_check_algorithm(
        const sensors::detail::sensor_reading_t& new_reading,
        const sensors::detail::sensor_reading_t& latest_reading)
        -> ext::boolean
{
    // If one of the readings doesn't contain the illuminance key, then no comparisons can be made, so state the
    // threshold has been surpassed, and return True.
    return_if (!new_reading.contains(u"illuminance")) true;
    return_if (!latest_reading.contains(u"illuminance")) true;

    // If the difference in values is under the given threshold, then return False, because there isn't a great enough
    // change in the 2 values to suggest that there has been a meaningful change.
    auto new_illuminance    = new_reading.at(u"illuminance").to<ext::number<double>>();
    auto latest_illuminance = latest_reading.at(u"illuminance").to<ext::number<double>>();
    return_if (ext::absolute(new_illuminance - latest_illuminance) < illuminance_threshold_value) false;

    // Round the two values using the quantization algorithm, and if the values are different, then the threshold has
    // been surpassed, so return True. Otherwise, the 2 values are too similar (round to same value), so return False.
    auto rounded_new_illuminance = reading_quantization_algorithm(new_reading);
    auto rounded_latest_illuminance = reading_quantization_algorithm(latest_reading);
    return rounded_new_illuminance != rounded_latest_illuminance;
}
