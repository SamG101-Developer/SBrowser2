#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_HPP

#include "dom_object.hpp"
namespace geolocation {class geolocation_coordinates;}
namespace geolocation {class geolocation_coordinates_private;}


class geolocation::geolocation_coordinates
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(geolocation_coordinates);
    MAKE_PIMPL(geolocation_coordinates);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(accuracy, ext::number<double>);
    DEFINE_GETTER(latitude, ext::number<double>);
    DEFINE_GETTER(longitude, ext::number<double>);
    DEFINE_GETTER(altitude, ext::number<double>);
    DEFINE_GETTER(altitude_accuracy, ext::number<double>);
    DEFINE_GETTER(heading, ext::number<double>);
    DEFINE_GETTER(speed, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_HPP
