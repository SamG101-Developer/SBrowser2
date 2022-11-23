#include "gravity_sensor.hpp"
#include "gravity_sensor_private.hpp"

#include "accelerometer/detail/abstract_operations_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"


accelerometer::gravity_sensor::gravity_sensor(detail::accelerometer_sensor_options_t&& options)
{
    INIT_PIMPL(gravity_sensor);

    // Construct aa GravitySensor instance using a detail algorithm, that runs certain checks for multiple similar
    // objects, tuned by the 'options' dictionary.
    detail::construct_accelerometer_object(this, std::move(options));
}


auto accelerometer::gravity_sensor::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<accelerometer>()
        .ctor<detail::accelerometer_local_coordinate_system_t&&>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
