module;
#include "ext/macros.hpp"


module apis.geolocation_sensor.geolocation_sensor;
import apis.geolocation_sensor.detail;

import apis.dom.abort_signal;
import apis.dom.dom_exception;
import apis.dom.detail;

import apis.sensors.sensor;
import apis.sensors.detail;
import apis.sensors.types;

import apis.web_idl.detail;

import ext.core;
import ext.js;
import js.env.module_type;
import js.env.realms;


geolocation_sensor::geolocation_sensor::geolocation_sensor(
        geolocation_sensor_options_t&& options)
{
    // Construct a GeolocationSensor instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_geolocation_sensor_object(this, std::move(options));
}


auto geolocation_sensor::geolocation_sensor::read(
        read_options_t&& read_options)
        -> ext::promise<geolocation_sensor_reading_t>
{
    auto promise = ext::promise<geolocation_sensor_reading_t>{};
    decltype(auto) signal = read_options[u"signal"].to<dom::abort_signal*>();
    auto e = js::env::env::current();
    auto sensor = geolocation_sensor{};
    JS_EXCEPTION_HANDLER;

    if (signal && dom::detail::is_signal_aborted(signal))
        return web_idl::detail::reject_promise(promise, e.js.realm(), signal->d_func()->abort_reason.to<dom::dom_exception*>());

    if (JS_EXCEPTION_HAS_THROWN)
        return web_idl::detail::reject_promise(promise, e.js.realm(), JS_EXCEPTION);

    sensor.start();
    if (signal)
        signal->d_func()->abort_algorithms.emplace_back(
                [&e, &sensor, &promise, signal]
                {sensor.stop(); web_idl::detail::reject_promise(promise, e.js.realm(), signal->d_func()->abort_reason.to<dom::dom_exception*>());});

    // TODO : async algorithm

    return promise;
}


auto geolocation_sensor::geolocation_sensor::get_latitude() const -> ext::number<double>
{
    // Get the latest reading for the "latitude" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_latitude = sensors::detail::get_value_from_latest_reading(this, u"latitude");
    auto defaulted_latitude = candidate_latitude.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_latitude = defaulted_latitude.at(u"latitude").to<ext::number<double>>();
    return extracted_latitude;
}


auto geolocation_sensor::geolocation_sensor::get_longitude() const -> ext::number<double>
{
    // Get the latest reading for the "longitude" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_longitude = sensors::detail::get_value_from_latest_reading(this, u"longitude");
    auto defaulted_longitude = candidate_longitude.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_longitude = defaulted_longitude.at(u"longitude").to<ext::number<double>>();
    return extracted_longitude;
}


auto geolocation_sensor::geolocation_sensor::get_altitude() const -> ext::number<double>
{
    // Get the latest reading for the "altitude" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_altitude = sensors::detail::get_value_from_latest_reading(this, u"altitude");
    auto defaulted_altitude = candidate_altitude.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_altitude = defaulted_altitude.at(u"altitude").to<ext::number<double>>();
    return extracted_altitude;
}


auto geolocation_sensor::geolocation_sensor::get_accuracy() const -> ext::number<double>
{
    // Get the latest reading for the "accuracy" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_accuracy = sensors::detail::get_value_from_latest_reading(this, u"accuracy");
    auto defaulted_accuracy = candidate_accuracy.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_accuracy = defaulted_accuracy.at(u"accuracy").to<ext::number<double>>();
    return extracted_accuracy;
}


auto geolocation_sensor::geolocation_sensor::get_altitude_accuracy() const -> ext::number<double>
{
    // Get the latest reading for the "altitude_accuracy" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_altitude_accuracy = sensors::detail::get_value_from_latest_reading(this, u"altitude_accuracy");
    auto defaulted_altitude_accuracy = candidate_altitude_accuracy.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_altitude_accuracy = defaulted_altitude_accuracy.at(u"altitude_accuracy").to<ext::number<double>>();
    return extracted_altitude_accuracy;
}


auto geolocation_sensor::geolocation_sensor::get_heading() const -> ext::number<double>
{
    // Get the latest reading for the "heading" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_heading = sensors::detail::get_value_from_latest_reading(this, u"heading");
    auto defaulted_heading = candidate_heading.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_heading = defaulted_heading.at(u"heading").to<ext::number<double>>();
    return extracted_heading;
}


auto geolocation_sensor::geolocation_sensor::get_speed() const -> ext::number<double>
{
    // Get the latest reading for the "speed" value, default it to 0 if it doesn't exist, and then convert it from
    // the ext::any type to a double. Return the double.
    auto candidate_speed = sensors::detail::get_value_from_latest_reading(this, u"speed");
    auto defaulted_speed = candidate_speed.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_speed = defaulted_speed.at(u"speed").to<ext::number<double>>();
    return extracted_speed;
}


auto geolocation_sensor::geolocation_sensor::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<sensors::sensor>()
        .ctor<geolocation_sensor_options_t&&>()
        .property("latitude", &geolocation_sensor::get_latitude)
        .property("longitude", &geolocation_sensor::get_longitude)
        .property("altitude", &geolocation_sensor::get_altitude)
        .property("accuracy", &geolocation_sensor::get_accuracy)
        .property("altitudeAccuracy", &geolocation_sensor::get_altitude_accuracy)
        .property("heading", &geolocation_sensor::get_heading)
        .property("speed", &geolocation_sensor::get_speed)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

