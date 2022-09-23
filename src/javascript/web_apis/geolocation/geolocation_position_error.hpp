#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP

#include "dom_object.hpp"
namespace geolocation {class geolocation_position_error;}


class geolocation::geolocation_position_error
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(geolocation_position_error);
    geolocation_position_error() = default;

public js_static_constants:
    constexpr static const ext::number<ushort> PERMISSION_DENIED = 1;
    constexpr static const ext::number<ushort> POSITION_UNAVAILABLE = 2;
    constexpr static const ext::number<ushort> TIMEOUT = 3;

private js_properties:
    ext::property<ext::number<ushort>> code;
    ext::property<ext::string> message;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_POSITION_ERROR_HPP
