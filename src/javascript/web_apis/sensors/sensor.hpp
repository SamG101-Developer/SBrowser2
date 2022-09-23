#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP

#include "dom/nodes/event_target.hpp"
namespace sensors {class sensor;}

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(sensors)


class sensors::sensor
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(sensor);
    MAKE_PIMPL(sensor);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto start() -> void;
    auto stop() -> void;

private js_properties:
    DEFINE_GETTER(activated, ext::boolean);
    DEFINE_GETTER(has_reading, ext::boolean);
    DEFINE_GETTER(timestamp, hr_time::dom_high_res_time_stamp);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP
