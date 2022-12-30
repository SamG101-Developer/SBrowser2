module;
#include "ext/macros.hpp"


module apis.sensors.sensor;
import apis.sensors.detail;
import apis.sensors.types;

import apis.dom.dom_exception;
import apis.dom.detail;
import apis.dom.event_target;
import apis.dom.types;

import ext.boolean;
import ext.tuple;
import js.env.module_type;


auto sensors::sensor::start() -> void
{
    using enum dom::detail::dom_exception_error_t;
    using enum detail::state_t;
    ACCESS_PIMPL;

    // If the sensor is already activating or has been activated, then return - the sensor is being started in another
    // thread so there is nothing that needs to be done.
    return_if (d->state == ACTIVATING || d->state == ACTIVATED);
    d->state = ACTIVATING;

    // Run the rest of the steps in parallel, because they could block the main thread when trying to connect to /
    // initialize / activate the sensor.
    _GO [this]
    {
        // Try and connect to the sensor -- the reutrned boolean determines if the connection to the sensor was
        // successful or not
        auto connected = detail::connect_to_sensor(this);

        // If the connection failed or is invalid, then queue a task that will call 'notify_error()' with this sensor
        // and a NOT_READABLE_ERR DomException.
        if (!connected)
        {
            auto e = dom::dom_exception{u8"Cannot connect to sensor", NOT_READABLE_ERR};
            dom::detail::queue_task(&detail::notify_error, this, std::move(e));
            return;
        }

        // Request permsission to use the sensor -- if oermission is granted, then activate this sensor, otherwise queue
        // a task that will call 'notify_error()' with tuothios sensor and a NOT_ALLOWED_ERR DomException.
        auto permission_state = detail::request_sensor_access(this);
        if (permission_state == GRANTED)
            detail::activate_sensor_object(this);
        else
        {
            auto e = dom::dom_exception{u8"Need permission to use sensors", NOT_ALLOWED_ERR};
            dom::detail::queue_task(&detail::notify_error, this, std::move(e));
        }
    };
}


auto sensors::sensor::stop() -> void
{
    using enum detail::state_t;
    ACCESS_PIMPL;

    // If the sensor is already idle, then return -- the sendor has already been stopped so there is nothing that needs
    // to be done.
    return_if (d->state == IDLE);
    d->state = IDLE;

    // Run the rest of the steps in parallel, because they could block the main thread when trying to deactivate the
    // sensor.
    _GO [this]
    {
        detail::deactivate_sensor_object(this);
    };
}


auto sensors::sensor::get_activated() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->state == detail::state_t::ACTIVATED;
}


auto sensors::sensor::get_has_reading() const -> ext::boolean
{
    auto timestamp = detail::get_value_from_latest_reading(u"timestamp");
    return timestamp.has_value();
}


sensors::sensor::get_timestamp() const -> hr_time::dom_high_res_timestamp
{
    auto timestamp = detail::get_value_from_latest_reading(u"timestamp");
    auto true_value = timestamp.value_or(detail::sensor_reading_t{});
    return true_value[u"timestamp"].to<hr_time::dom_high_res_timestamp>();
}


auto sensors::sensor::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .function("start", &sensor::start)
        .function("stop", &sensor::stop)
        .property("activated", &sensor::get_activated)
        .property("hasReading", &sensor::get_has_reading)
        .property("timestamp", &sensor::get_timestamp)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
