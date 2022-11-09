#include "device_posture.hpp"
#include "device_posture_private.hpp"


device_posture::device_posture::device_posture()
{
    INIT_PIMPL(device_posture);
}


auto device_posture::device_posture::get_type() const -> detail::device_posture_type_t
{
    ACCESS_PIMPL(const device_posture);
    return d->current_posture;
}


auto device_posture::device_posture::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<device_posture>{isolate}
        .inherit<dom_object>()
        .property("type", &device_posture::get_type)
        .auto_wrap_objects();

    return std::move(conversion);
}
