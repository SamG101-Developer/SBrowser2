#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_HPP

#include "dom_object.hpp"
namespace geolocation {class geolocation_position;}


#include USE_INNER_TYPES(high_resolution_time)
namespace geolocation {class geolocation_coordinates;}


class geolocation::geolocation_position
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(geolocation_position);
    geolocation_position();

public js_properties:
    ext::property<std::unique_ptr<geolocation_coordinates>> coords;
    ext::property<high_resolution_time::detail::epoch_time_stamp_t> timestamp;

private js_slots:
    ext::slot<ext::boolean> s_is_high_accuracy;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_HPP
