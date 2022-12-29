module;
#include "ext/macros/macros.hpp"


module apis.device_orientation.device_motion_event;
import apis.device_orientation.device_motion_event_private;
import apis.device_orientation.device_motion_event_acceleration;
import apis.dom.event;

import ext.core;


device_orientation::device_motion_event::device_motion_event(
        ext::string&& event_type,
        device_motion_event_init_t&& event_init)
        : dom::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->acceleration = nullptr;
    d->acceleration_including_gravity = nullptr;
    d->rotation_rate = nullptr;
}
