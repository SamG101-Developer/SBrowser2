#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_UNCALIBRATED_MAGNETOMETER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_UNCALIBRATED_MAGNETOMETER_HPP

#include "magnetometer/magnetometer.hpp"
namespace magnetometer {class uncalibrated_magnetometer;}
namespace magnetometer {class uncalibrated_magnetometer_private;}

#include INCLUDE_INNER_TYPES(magnetometer)


class magnetometer::uncalibrated_magnetometer
        : public magnetometer::magnetometer
{
public constructors:
    uncalibrated_magnetometer(detail::magnetometer_sensor_options_t&& options);
    DOM_CTORS(uncalibrated_magnetometer);
    MAKE_PIMPL(uncalibrated_magnetometer);
    MAKE_V8_AVAILABLE;

public cpp_accessors:
    DEFINE_GETTER(x_bias, ext::number<double>);
    DEFINE_GETTER(y_bias, ext::number<double>);
    DEFINE_GETTER(z_bias, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_UNCALIBRATED_MAGNETOMETER_HPP
