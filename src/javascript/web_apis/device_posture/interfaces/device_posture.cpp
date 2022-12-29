module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.device_posture.device_posture;
import apis.device_posture.device_posture_private ;
import apis.device_posture.types;

import ext.core;
import js.env.module_type;


device_posture::device_posture::device_posture()
{
    INIT_PIMPL;
}


auto device_posture::device_posture::get_type() const -> detail::device_posture_type_t
{
    // The 'type' getter returns the equivalent 'current_posture' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->current_posture;
}


auto device_posture::device_posture::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("type", &device_posture::get_type)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
