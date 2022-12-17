module;
#include "ext/macros/pimpl.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.device_orientation.device_motion_event_acceleration;
import apis.device_orientation.device_motion_event_acceleration_private;

import ext.number;
import ext.tuple;


device_orientation::device_motion_event_acceleration::device_motion_event_acceleration()
{
    INIT_PIMPL;
}


auto device_orientation::device_motion_event_acceleration::get_x() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->x;
}


auto device_orientation::device_motion_event_acceleration::get_y() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->y;
}


auto device_orientation::device_motion_event_acceleration::get_z() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->z;
}


auto device_orientation::device_motion_event_acceleration::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{}
