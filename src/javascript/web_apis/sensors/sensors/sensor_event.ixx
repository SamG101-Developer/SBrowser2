module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.sensors.sensor_event;
import apis.dom.event;

import ext.any;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;

namespace dom {class dom_exception;}


DEFINE_PUBLIC_CLASS(sensors, sensor_event)
        : public dom::event
{
public typedefs:
    using sensor_error_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    DOM_CTORS(sensor_event);
    sensor_event(ext::string&& event_type, sensor_error_event_init_t&& event_init = {});
    MAKE_PIMPL(sensor_event);
    MAKE_V8_AVAILABLE(WINDOW | DEDICATED_WORKER | SECURE);

private js_properties:
    DEFINE_GETTER(error, dom::dom_exception*);
};
