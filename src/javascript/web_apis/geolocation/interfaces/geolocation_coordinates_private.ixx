module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation_coordinates:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(geolocation, geolocation_coordinates)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(geolocation_coordinates);

public:
    ext::number<double> accuracy;
    ext::number<double> latitude;
    ext::number<double> longitude;

    ext::number<double> altitude;
    ext::number<double> altitude_accuracy;
    ext::number<double> heading;
    ext::number<double> speed;
};
