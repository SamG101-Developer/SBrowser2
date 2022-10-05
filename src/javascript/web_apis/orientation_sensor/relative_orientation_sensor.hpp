#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_RELATIVE_ORIENTATION_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_RELATIVE_ORIENTATION_SENSOR_HPP

// Inheritance Includes & This Class
#include "orientation_sensor/orientation_sensor.hpp"
namespace orientation_sensor {class relative_orientation_sensor;}
namespace orientation_sensor {class relative_orientation_sensor_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(orientation_sensor)


class orientation_sensor::relative_orientation_sensor
        : public orientation_sensor
{
public constructors:
    relative_orientation_sensor(detail::relative_orientation_sensor_options_t&& options);
    DOM_CTORS(relative_orientation_sensor);
    MAKE_PIMPL(relative_orientation_sensor);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_RELATIVE_ORIENTATION_SENSOR_HPP
