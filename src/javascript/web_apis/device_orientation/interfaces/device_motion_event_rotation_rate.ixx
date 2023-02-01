module;
#include "ext/macros.hpp"


export module apis.device_orientation.device_motion_event_rotation_rate;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(device_orientation, device_motion_event_rotation_rate)
        : public dom_object
{
public constructors:
    device_motion_event_rotation_rate();
    MAKE_PIMPL(device_motion_event_rotation_rate);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(alpha, ext::number<double>);
    DEFINE_GETTER(beta , ext::number<double>);
    DEFINE_GETTER(gamma, ext::number<double>);
};
