#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ABSOLUTE_ORIENTATION_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ABSOLUTE_ORIENTATION_SENSOR_HPP

#include "orientation_sensor/orientation_sensor.hpp"
namespace orientation_sensor {class absolute_orientation_sensor;}

#include INCLUDE_INNER_TYPES(orientation_sensor)

#include "absolute_orientation_sensor_private.hpp"


class orientation_sensor::absolute_orientation_sensor
        : public orientation_sensor
{
public constructors:
    absolute_orientation_sensor(detail::absolute_orientation_sensor_options_t&& options);
    DOM_CTORS(absolute_orientation_sensor);
    MAKE_PIMPL(absolute_orientation_sensor);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ABSOLUTE_ORIENTATION_SENSOR_HPP
