#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"



DEFINE_PRIVATE_CLASS(device_orientation, device_orientation_event)
        : virtual dom::events::event_private
{
    MAKE_QIMPL(device_orientation);

    ext::number<double> alpha;
    ext::number<double> beta;
    ext::number<double> gamma;
    ext::boolean absolute;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_PRIVATE_HPP
