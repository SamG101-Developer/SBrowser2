#include "abstract_operations_internals.hpp"

#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(sensors)
#include "dom/detail/exception_internals.hpp"
#include "magnetometer/magnetometer.hpp"
#include "sensors/detail/sensor_internals.hpp"


auto magnetometer::detail::construct_magnetometer_object(
        magnetometer* sensor,
        magnetometer_sensor_options_t&& options) -> void
{
    // If the sensor isn't allowed by a policy, then throw a SecurityError, letting the user know that using this sensor
    // isn't permitted.
    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [sensor] {return !sensors::detail::check_sensor_policy_controlled_features(*sensor->m_sensor);},
            ext::string{typeid(sensor).name()} + " cannot be created due to a failed check in the sensor policy controlled features");

    // Initialize the sensor object, and set the coordinate system of the sensor, depending on the "referenceFrame"
    // option from the 'options' dictionary.
    sensors::detail::initialize_sensor_object(sensor, std::move(options));
    sensor->m_coordinate_system = options.template try_emplace("referenceFrame").first->second.template to<ext::string>() == "screen"
            ? sensors::detail::coordinate_system_t::SCREEN_COORDINATE_SYSTEM
            : sensors::detail::coordinate_system_t::DEVICE_COORDINATE_SYSTEM;
}

