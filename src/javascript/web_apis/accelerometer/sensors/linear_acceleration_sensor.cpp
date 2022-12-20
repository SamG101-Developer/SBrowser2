module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.accelerometer.linear_acceleration_sensor;
import apis.accelerometer.linear_acceleration_sensor_private;
import apis.accelerometer.detail;

import ext.tuple;
import js.env.module_type;


accelerometer::linear_acceleration_sensor::linear_acceleration_sensor(detail::accelerometer_sensor_options_t&& options)
{
    INIT_PIMPL;

    // Construct a LinearAccelerometer instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}


auto accelerometer::linear_acceleration_sensor::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<accelerometer>()
        .ctor<detail::accelerometer_local_coordinate_system_t&&>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
