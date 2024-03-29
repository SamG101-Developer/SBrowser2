module;
#include <utility>


module apis.accelerometer.detail;

import apis.accelerometer.accelerometer;
import apis.accelerometer.types;

import apis.dom.detail;
import apis.dom.types;

import apis.sensors.detail;
import apis.sensors.types;

import ext.core;


auto accelerometer::detail::construct_accelerometer_object(
        accelerometer* sensor,
        ext::map<ext::string, ext::any>&& options)
        -> void
{
    using enum dom::detail::dom_exception_error_t;

    // If the sensor isn't allowed by a policy, then throw a SecurityError, letting the user know that using this sensor
    // isn't permitted.
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [sensor] {return !sensors::detail::check_sensor_policy_controlled_features(*sensor->d_func()->sensor);},
            u8"Accelerometer cannot be created due to a failed check in the sensor policy controlled features");

    // Initialize the sensor object, and set the coordinate system of the sensor, depending on the "referenceFrame"
    // option from the 'options' dictionary.
    using enum accelerometer_local_coordinate_system_t;
    sensors::detail::initialize_sensor_object(sensor, std::move(options));
    sensor->d_func()->coordinate_system = options[u"referenceFrame"].to<accelerometer_local_coordinate_system_t>() == SCREEN
            ? sensors::detail::coordinate_system_t::SCREEN_COORDINATE_SYSTEM
            : sensors::detail::coordinate_system_t::DEVICE_COORDINATE_SYSTEM;
}
