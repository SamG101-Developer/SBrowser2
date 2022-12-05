#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(hr_time)
namespace geolocation {class geolocation_coordinates;}


DEFINE_PRIVATE_CLASS(geolocation, geolocation_position) : virtual dom_object_private
{
    std::unique_ptr<geolocation_coordinates> coords;
    hr_time::epoch_time_stamp timestamp;
    ext::boolean is_high_accuracy;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_PRIVATE_HPP
