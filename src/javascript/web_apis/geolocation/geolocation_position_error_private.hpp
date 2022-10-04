#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "base_exception.hpp"

#include INCLUDE_INNER_TYPES(geolocation)


DEFINE_PRIVATE_CLASS(geolocation, geolocation_position_error) : base_exception<geolocation::detail::geolocation_position_error_t> {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_PRIVATE_HPP
