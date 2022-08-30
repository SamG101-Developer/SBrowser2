#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace geolocation_sensor::detail
{
    using geolocation_sensor_options_t = ext::map<ext::string, ext::any>;
    using geolocation_sensor_reading_t = ext::map<ext::string, ext::any>;
    using read_options_t = ext::map<ext::string, ext::any>;
    using geolocation_reading_values_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_SENSOR__TYPEDEFS_HPP
