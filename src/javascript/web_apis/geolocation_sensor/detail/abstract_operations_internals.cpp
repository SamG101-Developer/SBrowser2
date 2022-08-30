#include "abstract_operations_internals.hpp"

#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(geolocation_sensor)
#include "dom/detail/exception_internals.hpp"
#include "geolocation_sensor/geolocation_sensor.hpp"
#include "sensors/detail/sensor_internals.hpp"


auto geolocation_sensor::detail::construct_geolocation_sensor_object(
        geolocation_sensor* sensor,
        geolocation_sensor_options_t&& options)
        -> void
{
    // If the sensor isn't allowed by a policy, then throw a SecurityError, letting the user know that using this sensor
    // isn't permitted.
    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [sensor] {return !sensors::detail::check_sensor_policy_controlled_features(*sensor->m_sensor);},
            ext::string{typeid(sensor).name()} + " cannot be created due to a failed check in the sensor policy controlled features");

    // Initialize the sensor object, and set the coordinate system of the sensor, depending on the "referenceFrame"
    // option from the 'options' dictionary.
    sensors::detail::initialize_sensor_object(sensor, std::move(options));
}


auto geolocation_sensor::detail::resolve_geolocation_promise(
        geolocation_sensor* sensor,
        ext::promise<geolocation_sensor_reading_t>& promise)
        -> void
{
    geolocation_sensor_reading_t reading;
    auto latest_reading = sensors::detail::get_value_from_latest_reading(sensor, "geolocation");
    reading = latest_reading.has_value() ? std::move(*latest_reading) : geolocation_sensor_reading_t{};
    sensor->stop();
    promise.resolve(std::move(reading));
}
