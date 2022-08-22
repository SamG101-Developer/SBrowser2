#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP

#include "dom/nodes/event_target.hpp"
namespace sensors {class sensor;}

#include "ext/boolean.hpp"
#include USE_INNER_TYPES(high_resolution_time)
#include USE_INNER_TYPES(sensors)


class sensors::sensor
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(sensor);
    sensor() = default;

public js_methods:
    auto start() -> void;
    auto stop() -> void;

public js_properties:
    ext::property<ext::boolean> activated;
    ext::property<ext::boolean> has_reading;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> timestamp;

private js_slots:
    detail::state_t s_state;
    ext::number<double> s_frequency;
    high_resolution_time::detail::dom_high_res_time_stamp_t s_last_event_fired_at;
    ext::boolean s_pending_reading_notification;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP
