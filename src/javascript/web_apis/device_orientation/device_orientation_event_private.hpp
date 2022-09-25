#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_PRIVATE_HPP

#include "dom/events/event.hpp"

#include "ext/pimpl.hpp"


DEFINE_PRIVATE_CLASS(device_orientation, device_orientation_event)
{
    ext::number<double> alpha;
    ext::number<double> beta;
    ext::number<double> gamma;
    ext::boolean absolute;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_PRIVATE_HPP