module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"


module apis.accelerometer.gravity_sensor;
import apis.accelerometer.gravity_sensor_private;
import apis.accelerometer.detail;

import ext.tuple;
import js.env.module_type;


accelerometer::gravity_sensor::gravity_sensor(accelerometer_sensor_options_t&& options)
{
    INIT_PIMPL;

    // Construct aa GravitySensor instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}


auto accelerometer::gravity_sensor::_to_v8(
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
