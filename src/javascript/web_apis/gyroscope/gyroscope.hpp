#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_GYROSCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_GYROSCOPE_HPP

#include "sensors/sensor.hpp"
namespace gyroscope {class gyroscope;}
namespace gyroscope {class gyroscope_private;}

#include INCLUDE_INNER_TYPES(gyroscope)


class gyroscope::gyroscope
        : public sensors::sensor
{
public constructors:
    DOM_CTORS(gyroscope);
    gyroscope(detail::gyroscope_sensor_options_t&& sensor_options);
    MAKE_PIMPL(gyroscope);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_GYROSCOPE_HPP
