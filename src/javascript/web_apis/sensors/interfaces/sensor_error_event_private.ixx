module;
#include "ext/macros.hpp"


export module apis.sensors.sensor_error_event:p;
import apis.dom.event;

namespace dom {class dom_exception;}


DEFINE_PRIVATE_CLASS(sensors, sensor_error_event) : dom::event_private
{
    std::unique_ptr<dom::dom_exception> error;
};
