module;
#include "ext/macros/pimpl.hpp"


export module apis.sensors.sensor_error_event_private;
import apis.dom.event_private;

namespace dom {class dom_exception;}


DEFINE_PRIVATE_CLASS(sensors, sensor_error_event) : dom::event_private
{
    std::unique_ptr<dom::dom_exception> error;
};
