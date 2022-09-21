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
    sensor() = default;

public js_methods:
    auto start() -> void;
    auto stop() -> void;

public js_properties:
    ext::property<ext::boolean> activated;
    ext::property<ext::boolean> has_reading;
    ext::property<hr_time::dom_high_res_time_stamp> timestamp;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private js_slots:
    detail::state_t s_state;
    ext::number<double> s_frequency;
    hr_time::dom_high_res_time_stamp s_last_event_fired_at;
    ext::boolean s_pending_reading_notification;

private cpp_properties:
    detail::coordinate_system_t m_coordinate_system;
    std::unique_ptr<detail::sensor_type_t> m_sensor;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_HPP
