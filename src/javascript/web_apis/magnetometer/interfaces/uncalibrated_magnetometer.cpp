module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.magnetometer.uncalibrated_magnetometer;
import apis.magnetometer.detail;

import apis.sensors.detail;
import apis.sensors.types;

import ext.core;
import js.env.module_type;


magnetometer::uncalibrated_magnetometer::uncalibrated_magnetometer(
        uncalibrated_magnetometer_sensor_options_t&& options)
{
    INIT_PIMPL;

    // Construct a Magnetometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_magnetometer_object(this, std::move(options));
}


auto magnetometer::uncalibrated_magnetometer::get_x_bias() const -> ext::number<double>
{
    // Get the latest reading for the "x" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_x_bias = sensors::detail::get_value_from_latest_reading(this, u"xBias");
    auto defaulted_x_bias = candidate_x_bias.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_x_bias = defaulted_x_bias.at(u"xBias").to<ext::number<double>>();
    return extracted_x_bias;
}


auto magnetometer::uncalibrated_magnetometer::get_y_bias() const -> ext::number<double>
{
    // Get the latest reading for the "y" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_y_bias = sensors::detail::get_value_from_latest_reading(this, u"yBias");
    auto defaulted_y_bias = candidate_y_bias.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_y_bias = defaulted_y_bias.at(u"yBias").to<ext::number<double>>();
    return extracted_y_bias;
}


auto magnetometer::uncalibrated_magnetometer::get_z_bias() const -> ext::number<double>
{
    // Get the latest reading for the "z" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_z_bias = sensors::detail::get_value_from_latest_reading(this, u"zBias");
    auto defaulted_z_bias = candidate_z_bias.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_z_bias = defaulted_z_bias.at(u"z").to<ext::number<double>>();
    return extracted_z_bias;
}


auto magnetometer::uncalibrated_magnetometer::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<sensors::sensor>()
        .ctor<uncalibrated_magnetometer_sensor_options_t&&>()
        .property("xBias", &uncalibrated_magnetometer::get_x_bias)
        .property("yBias", &uncalibrated_magnetometer::get_y_bias)
        .property("zBias", &uncalibrated_magnetometer::get_z_bias)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
