#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP

#include "dom/nodes/event_target.hpp"
namespace device_posture {class device_posture;}

#include "device_posture/device_posture_private.hpp"
#include INCLUDE_INNER_TYPES(device_posture)

class device_posture::device_posture
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(device_posture);
    device_posture() = default;

    MAKE_PIMPL(device_posture);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_GETTER(type, detail::device_posture_type_t) {return d_ptr->current_posture;}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP
