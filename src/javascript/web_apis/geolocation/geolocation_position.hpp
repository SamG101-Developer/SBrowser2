#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_HPP


namespace geolocation {class geolocation_position;}
namespace geolocation {class geolocation_position_private;}

#include INCLUDE_INNER_TYPES(hr_time)
namespace geolocation {class geolocation_coordinates;}


class geolocation::geolocation_position
        : public virtual dom_object
{
public constructors:
    geolocation_position();
    MAKE_PIMPL(geolocation_position);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(coords, geolocation_coordinates*);
    DEFINE_GETTER(timestamp, hr_time::epoch_time_stamp);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_HPP
