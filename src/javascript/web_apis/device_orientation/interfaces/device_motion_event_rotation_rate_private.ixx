module;
#include "ext/macros.hpp"


export module apis.device_orientation.device_motion_event_rotation_rate:p;
import apis.dom_object;


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