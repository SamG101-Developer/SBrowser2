module;
#include "ext/macros.hpp"


export module apis.sensors.sensor;
import apis.dom.event_target;

import ext.any;
import ext.boolean;
import ext.map;
import ext.tuple;
import ext.string;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(sensors, sensor)
        : public dom::event_target
{
public typedefs:
    using sensor_options_t = ext::map<ext::string, ext::any>;

public constructors:
    DOM_CTORS(sensor);
    MAKE_PIMPL(sensor);
    MAKE_V8_AVAILABLE(WINDOW | DEDICATED_WORKER | SECURE);

public js_methods:
    auto start() -> void;
    auto stop() -> void;

private js_properties:
    DEFINE_GETTER(activated, ext::boolean);
    DEFINE_GETTER(has_reading, ext::boolean);
    DEFINE_GETTER(timestamp, hr_time::dom_high_res_time_stamp);
};
