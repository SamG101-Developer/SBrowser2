module;
#include "ext/macros.hpp"


export module apis.device_posture.device_posture:p;
import apis.dom.event_target;

IMPORT_ALL_TYPES(device_posture);


DEFINE_PRIVATE_CLASS(device_posture, device_posture) final
        : dom::event_target_private
{
public:
    MAKE_QIMPL(device_posture);

public:
    detail::device_posture_type_t current_posture;
};
