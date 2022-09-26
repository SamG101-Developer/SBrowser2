#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP

#include "dom/other/dom_exception.hpp"
namespace geolocation {class geolocation_position_error;}

#include "geolocation_position_error_private.hpp"


class geolocation::geolocation_position_error
        : public dom::other::dom_exception
{
public constructors:
    DOM_CTORS(geolocation_position_error);
    MAKE_PIMPL(geolocation_position_error);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP
