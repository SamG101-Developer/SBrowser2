module apis.geolocation_sensor.detail;
import apis.geolocation_sensor.geolocation_sensor;

import ext.core;
import ext.js;


auto geolocation_sensor::detail::construct_geolocation_sensor_object(
        geolocation_sensor* sensor,
        geolocation_sensor_options_t&& options)
        -> void
{
    using enum dom::detail::dom_exception_error_t;

    // If the sensor isn't allowed by a policy, then throw a SecurityError, letting the user know that using this sensor
    // isn't permitted.
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [sensor] {return !sensors::detail::check_sensor_policy_controlled_features(*sensor->d_func()->sensor);},
            u8"GeolocationSensor cannot be created due to a failed check in the sensor policy controlled features");

    // Initialize the sensor object, and set the coordinate system of the sensor, depending on the "referenceFrame"
    // option from the 'options' dictionary.
    sensors::detail::initialize_sensor_object(sensor, std::move(options));
}


auto geolocation_sensor::detail::resolve_geolocation_promise(
        geolocation_sensor* sensor,
        ext::promise<geolocation_sensor_reading_t>& promise)
        -> void
{
    auto e = js::env::env::relevant(this);

    auto reading = geolocation_sensor_reading_t{};
    auto latest_reading = sensors::detail::get_value_from_latest_reading(sensor, u"geolocation");
    reading = latest_reading.has_value() ? std::move(*latest_reading) : geolocation_sensor_reading_t{};
    sensor->stop();

    web_idl::detail::resolve_promise(std::move(reading), e.js.realm());
}
