module;
#include "ext/macros.hpp"


export module apis.device_orientation.device_motion_event;
import apis.dom.event;

IMPORT_ALL_TYPES(device_orientation);


DEFINE_PUBLIC_CLASS(device_orientation, device_motion_event) final
        : public dom::event
{
public typedefs:
    using device_motion_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    device_motion_event(ext::string&& event_type, device_motion_event_init_t&& event_init = {});
    MAKE_PIMPL(device_motion_event);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_methods:
    auto request_permisison() -> ext::boolean;

private js_properties:
    DEFINE_GETTER(acceleration, device_motion_event_acceleration*);
    DEFINE_GETTER(acceleration_inlcuding_gravity, device_motion_event_acceleration*);
    DEFINE_GETTER(rotation_rate, device_motion_event_rotation_rate*);
    DEFINE_GETTER(interval, ext::number<double>);
};
