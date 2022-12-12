module;
#include "ext/macros/custom_operators.hpp"
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"


module apis.sensors.sensor;
import apis.sensors.sensor_private;
import apis.sensors.detail;
import apis.sensors.types;

import apis.dom.dom_exception;
import apis.dom.types;


auto sensors::sensor::start() -> void
{
    using enum detail::state_t;
    ACCESS_PIMPL;

    return_if (d->state == ACTIVATING || d->state == ACTIVATED);
    d->state = ACTIVATING;

    _GO [d]
    {
        auto connected = detail::connect_to_sensor(this);
        if (!connected)
        {
            using dom::detail::dom_exception_type_t;
            auto e = dom::dom_exception{NOT_READABLE_ERR, u8"Cannot connect to sensor"};
            dom::detail::queue_task()
        }
    };
}
