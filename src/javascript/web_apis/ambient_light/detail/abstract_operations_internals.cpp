#include "abstract_operations_internals.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "ambient_light/ambient_light_sensor.hpp"
#include "ambient_light/ambient_light_sensor_private.hpp"

#include "sensors/_typedefs.hpp"
#include "sensors/detail/sensor_internals.hpp"


auto ambient_light_sensor::detail::construct_ambient_light_sensor_object(
        ambient_light_sensor* sensor,
        sensors::detail::sensor_options_t&& options) -> ambient_light_sensor
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


auto ambient_light_sensor::detail::ambient_light_threshold_check_algorithm(
        sensors::detail::sensor_reading_t&& new_reading,
        sensors::detail::sensor_reading_t&& latest_reading)
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
    auto rounded_new_illuminance = sensors::detail::reading_quantization_algorithm<ambient_light_sensor>(std::move(new_reading));
    auto rounded_latest_illuminance = sensors::detail::reading_quantization_algorithm<ambient_light_sensor>(std::move(latest_reading));
    return rounded_new_illuminance != rounded_latest_illuminance;
}
