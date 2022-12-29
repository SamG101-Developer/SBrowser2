module;
#include "ext/macros/macros.hpp"


export module apis.device_posture.device_posture_private;
import apis.dom.event_target_private;
import apis.device_posture.types;


DEFINE_PRIVATE_CLASS(device_posture, device_posture) final
        : dom::event_target_private
{
public:
    MAKE_QIMPL(device_posture);

public:
    detail::device_posture_type_t current_posture;
};
