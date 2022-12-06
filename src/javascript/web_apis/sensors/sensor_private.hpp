#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(sensors)


DEFINE_PRIVATE_CLASS(sensors, sensor) : dom::nodes::event_target_private
{
    detail::state_t state;
    detail::coordinate_system_t coordinate_system;
    std::unique_ptr<detail::sensor_type_t> sensor;
    ext::number<double> frequency;
    hr_time::dom_high_res_time_stamp last_event_fired_at;
    ext::boolean pending_reading_notification;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_PRIVATE_HPP
