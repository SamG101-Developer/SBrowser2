module;
#include "ext/macros.hpp"

export module apis.geolocation.geolocation_position:p;
import apis.dom_object;

import apis.geolocation.types;
import apis.hr_time.types;


DEFINE_PRIVATE_CLASS(geolocation, geolocation_position)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(geolocation_position);

public:
    std::unique_ptr<geolocation_coordinates> coords;
    hr_time::epoch_time_stamp timestamp;
    ext::boolean is_high_accuracy;
};
