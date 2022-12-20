module;
#include "ext/macros/pimpl.hpp"


export module apis.device_orientation.device_motion_event_rotation_rate_private;
import apis.dom_object_private;

import ext.number;


DEFINE_PRIVATE_CLASS(device_orientation, device_motion_event_rotation_rate)
        : dom_object_private
{
public:
    MAKE_QIMPL(device_motion_event_rotation_rate);

public:
    ext::number<double> alpha;
    ext::number<double> beta;
    ext::number<double> gamma;
};