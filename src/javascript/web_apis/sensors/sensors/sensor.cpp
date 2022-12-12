module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"


module apis.sensors.sensor;
import apis.sensors.sensor_private;
import apis.sensors.detail;
import apis.sensors.types;


auto sensors::sensor::start() -> void
{
    using enum detail::state_t;
    ACCESS_PIMPL;

    return_if (d->state == ACTIVATING || d->state == ACTIVATED);
    d->state = ACTIVATING;

    _GO [d]
    {
        auto connected = d->connect_to_sensor();
    };
}
