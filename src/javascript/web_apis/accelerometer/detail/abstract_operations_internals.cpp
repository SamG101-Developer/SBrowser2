#include "abstract_operations_internals.hpp"

#include INCLUDE_INNER_TYPES(accelerometer)
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(sensors)
#include "dom/detail/exception_internals.hpp"
#include "accelerometer/accelerometer.hpp"
#include "sensors/detail/sensor_internals.hpp"

#include <typeinfo>


auto accelerometer::detail::construct_accelerometer_object(
        accelerometer* sensor,
        accelerometer_sensor_options_t&& options) -> void
{
    // If the sensor isn't allowed by a policy, then throw a SecurityError, letting the user know that using this sensor
    // isn't permitted.
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [sensor] {return !sensors::detail::check_sensor_policy_controlled_features(*sensor->m_sensor);},
            ext::string{typeid(sensor).name()}
                    + " cannot be created due to a failed check in the sensor policy controlled features");

    // Initialize the sensor object, and set the coordinate system of the sensor, depending on the "referenceFrame"
    // option from the 'options' dictionary.
    using enum accelerometer_local_coordinate_system_t;
    sensors::detail::initialize_sensor_object(sensor, std::move(options));
    sensor->d_func()->coordinate_system = options["referenceFrame"].to<accelerometer_local_coordinate_system_t>() == SCREEN
            ? sensors::detail::coordinate_system_t::SCREEN_COORDINATE_SYSTEM
            : sensors::detail::coordinate_system_t::DEVICE_COORDINATE_SYSTEM;
}
