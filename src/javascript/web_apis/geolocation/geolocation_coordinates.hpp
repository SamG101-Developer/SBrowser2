#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_HPP

#include "dom_object.hpp"
namespace geolocation {class geolocation_coordinates;}


class geolocation::geolocation_coordinates
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(geolocation_coordinates);
    geolocation_coordinates() = default;

private js_properties:
    ext::property<ext::number<double>> accuracy;
    ext::property<ext::number<double>> latitude;
    ext::property<ext::number<double>> longitude;
    ext::property<ext::number<double>> altitude;
    ext::property<ext::number<double>> altitude_accuracy;
    ext::property<ext::number<double>> heading;
    ext::property<ext::number<double>> speed;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_COORDINATES_HPP
