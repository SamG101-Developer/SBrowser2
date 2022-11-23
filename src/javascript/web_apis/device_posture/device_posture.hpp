#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP

#include "dom/nodes/event_target.hpp"
namespace device_posture {class device_posture;}
namespace device_posture {class device_posture_private;}

#include INCLUDE_INNER_TYPES(device_posture)


class device_posture::device_posture
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(device_posture);
    MAKE_PIMPL(device_posture);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(type, detail::device_posture_type_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP
