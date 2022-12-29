module;
#include "ext/macros/pimpl.hpp"


export module apis.device_orientation.device_motion_event_private;
import apis.dom.event_private;

import apis.device_orientation.types;
import ext.core;


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
