module;
#include "ext/macros/pimpl.hpp"
#include <tl/optional.hpp>


export module apis.sensors.sensor_private;
import apis.dom.event_target_private;

import apis.sensors.types;
import ext.number;
import ext.boolean;
import ext.string;
import ext.optional;


DEFINE_PRIVATE_CLASS(sensors, sensor)
        : dom::event_target_private
{
    detail::state_t state;
    detail::coordinate_system_t coordinate_system;
    std::unique_ptr<detail::sensor_type_t> sensor;
    ext::number<double> frequency;
    hr_time::dom_high_res_time_stamp last_event_fired_at;
    ext::boolean pending_reading_notification;
};
