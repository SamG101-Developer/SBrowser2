module;
#include "ext/macros.hpp"


export module apis.device_orientation.device_motion_event:p;
import apis.dom.event;

IMPORT_ALL_TYPES(device_orientation);


DEFINE_PRIVATE_CLASS(device_orientation, device_motion_event) final
        : dom::event_private
{
public:
    MAKE_QIMPL(device_motion_event);

public:
    std::unique_ptr<device_motion_event_acceleration> acceleration;
    std::unique_ptr<device_motion_event_acceleration> acceleration_including_gravity;
    std::unique_ptr<device_motion_event_rotation_rate> rotation_rate;
    ext::number<double> interval;
};
