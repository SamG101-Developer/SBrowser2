module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation_position;
import apis.dom_object;

import apis.geolcation.types;
import apis.hr_time.types;


DEFINE_PUBLIC_CLASS(geolocation, geolocation_position) final
        : public virtual dom_object
{
public constructors:
    geolocation_position();
    MAKE_PIMPL(geolocation_position);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(coords, geolocation_coordinates*);
    DEFINE_GETTER(timestamp, hr_time::epoch_time_stamp);
};
