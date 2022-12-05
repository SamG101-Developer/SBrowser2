#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP

#include "base_exception.ixx"
namespace geolocation {class geolocation_position_error;}
namespace geolocation {class geolocation_position_error_private;}

#include INCLUDE_INNER_TYPES(geolocation)


class geolocation::geolocation_position_error
        : public base_exception<detail::geolocation_position_error_t>
{
public constructors:
    geolocation_position_error();
    geolocation_position_error(ext::string&& message, exception_t type);
    MAKE_PIMPL(geolocation_position_error);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP
