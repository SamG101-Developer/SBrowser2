#include "device_posture.hpp"
#include "device_posture_private.hpp"


device_posture::device_posture::device_posture()
{
    INIT_PIMPL(device_posture);
}


auto device_posture::device_posture::get_type() const -> detail::device_posture_type_t
{
    // The 'type' getter returns the equivalent 'current_posture' attribute value that is stored in the private class.
    ACCESS_PIMPL(const device_posture);
    return d->current_posture;
}


auto device_posture::device_posture::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("type", &device_posture::get_type)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
