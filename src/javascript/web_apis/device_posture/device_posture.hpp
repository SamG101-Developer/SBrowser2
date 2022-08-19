#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP

#include "dom/nodes/event_target.hpp"
namespace device_posture {class device_posture;}

#include USE_INNER_TYPES(device_posture)

class device_posture::device_posture
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(device_posture);
    device_posture() = default;

public js_properties:
    ext::property<detail::device_posture_type_t> type;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_HPP
