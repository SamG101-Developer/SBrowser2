module;
#include "ext/macros.hpp"


export module apis.device_orientation.device_orientation_event:p;
import apis.dom.event;


DEFINE_PRIVATE_CLASS(device_orientation, device_orientation_event) final
        : virtual dom::event_private
{
    MAKE_QIMPL(device_orientation_event);

    ext::number<double> alpha;
    ext::number<double> beta;
    ext::number<double> gamma;
    ext::boolean absolute;
};
