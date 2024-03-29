module;
#include "ext/macros.hpp"


export module apis.device_orientation.device_motion_event_acceleration:p;
import apis.dom_object;

import ext.core;


DEFINE_PRIVATE_CLASS(device_orientation, device_motion_event_acceleration)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(device_motion_event_acceleration);

public:
    ext::number<double> x;
    ext::number<double> y;
    ext::number<double> z;
};
