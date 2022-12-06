#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(device_posture)


DEFINE_PRIVATE_CLASS(device_posture, device_posture)
        : dom::nodes::event_target_private
{
    MAKE_QIMPL(device_posture);

    detail::device_posture_type_t current_posture;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DEVICE_POSTURE_PRIVATE_HPP
