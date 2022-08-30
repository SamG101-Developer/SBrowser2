#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/promise.hpp"
#include USE_INNER_TYPES(geolocation_sensor)
namespace geolocation_sensor {class geolocation_sensor;}


namespace geolocation_sensor::detail
{
    auto construct_geolocation_sensor_object(
            geolocation_sensor* sensor,
            geolocation_sensor_options_t&& options)
            -> void;

    auto resolve_geolocation_promise(
            geolocation_sensor* sensor,
            ext::promise<geolocation_sensor_reading_t>& promise)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
