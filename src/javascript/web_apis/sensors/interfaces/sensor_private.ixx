module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


export module apis.sensors.sensor:p;
import apis.dom.event_target;

IMPORT_ALL_TYPES(sensors);


DEFINE_PRIVATE_CLASS(sensors, sensor)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(sensor);

public:
    detail::state_t state;
    detail::coordinate_system_t coordinate_system;
    std::unique_ptr<detail::sensor_type_t> sensor_type;
    std::unique_ptr<detail::platform_sensor_t> platform_sensor;
    ext::number<double> frequency;
    hr_time::dom_high_res_time_stamp last_event_fired_at;
    ext::boolean pending_reading_notification;
};
