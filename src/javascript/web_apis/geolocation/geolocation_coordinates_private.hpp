#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"




DEFINE_PRIVATE_CLASS(geolocation, geolocation_coordinates) : virtual dom_object_private
{
    ext::number<double> accuracy;
    ext::number<double> latitude;
    ext::number<double> longitude;

    ext::number<double> altitude;
    ext::number<double> altitude_accuracy;
    ext::number<double> heading;
    ext::number<double> speed;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_PRIVATE_HPP
