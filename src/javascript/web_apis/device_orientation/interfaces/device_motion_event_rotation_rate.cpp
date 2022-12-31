module;
#include "ext/macros.hpp"


module apis.device_orientation.device_motion_event_rotation_rate;

import ext.core;
import js.env.module_type;


device_orientation::device_motion_event_rotation_rate::device_motion_event_rotation_rate()
{
    INIT_PIMPL;
}


auto device_orientation::device_motion_event_rotation_rate::get_alpha() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->alpha;
}


auto device_orientation::device_motion_event_rotation_rate::get_beta() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->beta;
}


auto device_orientation::device_motion_event_rotation_rate::get_gamma() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->gamma;
}


auto device_orientation::device_motion_event_rotation_rate::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("alpha", &device_motion_event_rotation_rate::get_alpha)
        .property("beta" , &device_motion_event_rotation_rate::get_beta)
        .property("gamma", &device_motion_event_rotation_rate::get_gamma)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
