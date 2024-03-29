module;
#include "ext/macros.hpp"


export module apis.sensors.sensor_error_event;
import apis.dom.event;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(sensors, sensor_error_event)
        : public dom::event
{
public typedefs:
    using sensor_error_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    DOM_CTORS(sensor_error_event);
    sensor_error_event(ext::string&& event_type, sensor_error_event_init_t&& event_init = {});
    MAKE_PIMPL(sensor_error_event);
    MAKE_V8_AVAILABLE(WINDOW | DEDICATED_WORKER | SECURE);

private js_properties:
    DEFINE_GETTER(error, dom::dom_exception*);
};
