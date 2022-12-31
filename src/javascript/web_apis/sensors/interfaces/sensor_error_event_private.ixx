module;
#include "ext/macros.hpp"


export module apis.sensors.sensor_error_event:p;
import apis.dom.event;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(sensors, sensor_error_event) : dom::event_private
{
public:
    MAKE_QIMPL(sensor_error_event);

public:
    std::unique_ptr<dom::dom_exception> error;
};
