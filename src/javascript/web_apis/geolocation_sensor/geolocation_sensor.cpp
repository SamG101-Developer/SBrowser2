#include "geolocation_sensor.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/other/dom_exception.hpp"

#include "geolocation_sensor/detail/abstract_operations_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"


geolocation_sensor::geolocation_sensor::geolocation_sensor(
        detail::geolocation_sensor_options_t&& options)
{
    // Construct a GeolocationSensor instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_geolocation_sensor_object(this, std::move(options));
}


auto geolocation_sensor::geolocation_sensor::read(
        detail::read_options_t&& read_options)
        -> ext::promise<detail::geolocation_sensor_reading_t>
{
    ext::promise<detail::geolocation_sensor_reading_t> promise;
    decltype(auto) signal = read_options.try_emplace("signal", nullptr).first->second.to<dom::abort::abort_signal*>();

    if (signal && signal->aborted())
        return promise.reject(signal->reason().to<dom::other::dom_exception*>());

    JS_EXCEPTION_HANDLER;
    geolocation_sensor sensor {};

    if (JS_EXCEPTION_HAS_THROWN)
    {
        JS_REALM_GET_CURRENT;
        return promise.reject(v8pp::from_v8<dom::other::dom_exception>(current_agent, JS_EXCEPTION));
    }

    sensor.start();
    if (signal)
        signal->m_abort_algorithms.emplace_back(
                [&sensor, &promise, signal]
                {sensor.stop(); promise.reject(signal->reason().to<dom::other::dom_exception*>());});

    // TODO : async algorithm

    return promise;
}


auto geolocation_sensor::geolocation_sensor::get_latitude()
        const -> decltype(this->latitude)::value_t
{
    // Get the latest reading for the "latitude" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_latitude = sensors::detail::get_value_from_latest_reading(this, "latitude");
    auto defaulted_latitude = candidate_latitude.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_latitude = defaulted_latitude.at("latitude").to<ext::number<double>>();
    return extracted_latitude;
}


auto geolocation_sensor::geolocation_sensor::get_longitude()
        const -> decltype(this->longitude)::value_t
{
    // Get the latest reading for the "longitude" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_longitude = sensors::detail::get_value_from_latest_reading(this, "longitude");
    auto defaulted_longitude = candidate_longitude.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_longitude = defaulted_longitude.at("longitude").to<ext::number<double>>();
    return extracted_longitude;
}


auto geolocation_sensor::geolocation_sensor::get_altitude()
        const -> decltype(this->altitude)::value_t
{
    // Get the latest reading for the "altitude" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_altitude = sensors::detail::get_value_from_latest_reading(this, "altitude");
    auto defaulted_altitude = candidate_altitude.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_altitude = defaulted_altitude.at("altitude").to<ext::number<double>>();
    return extracted_altitude;
}


auto geolocation_sensor::geolocation_sensor::get_accuracy()
        const -> decltype(this->accuracy)::value_t
{
    // Get the latest reading for the "accuracy" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_accuracy = sensors::detail::get_value_from_latest_reading(this, "accuracy");
    auto defaulted_accuracy = candidate_accuracy.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_accuracy = defaulted_accuracy.at("accuracy").to<ext::number<double>>();
    return extracted_accuracy;
}


auto geolocation_sensor::geolocation_sensor::get_altitude_accuracy()
        const -> decltype(this->altitude_accuracy)::value_t
{
    // Get the latest reading for the "altitude_accuracy" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_altitude_accuracy = sensors::detail::get_value_from_latest_reading(this, "altitude_accuracy");
    auto defaulted_altitude_accuracy = candidate_altitude_accuracy.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_altitude_accuracy = defaulted_altitude_accuracy.at("altitude_accuracy").to<ext::number<double>>();
    return extracted_altitude_accuracy;
}


auto geolocation_sensor::geolocation_sensor::get_heading()
        const -> decltype(this->heading)::value_t
{
    // Get the latest reading for the "heading" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_heading = sensors::detail::get_value_from_latest_reading(this, "heading");
    auto defaulted_heading = candidate_heading.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_heading = defaulted_heading.at("heading").to<ext::number<double>>();
    return extracted_heading;
}


auto geolocation_sensor::geolocation_sensor::get_speed()
        const -> decltype(this->speed)::value_t
{
    // Get the latest reading for the "speed" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_speed = sensors::detail::get_value_from_latest_reading(this, "speed");
    auto defaulted_speed = candidate_speed.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_speed = defaulted_speed.at("speed").to<ext::number<double>>();
    return extracted_speed;
}

