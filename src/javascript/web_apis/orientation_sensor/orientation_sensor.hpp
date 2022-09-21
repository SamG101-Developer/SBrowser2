#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ORIENTATION_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ORIENTATION_SENSOR_HPP

#include "sensors/sensor.hpp"
namespace orientation_sensor {class orientation_sensor;}

#include INCLUDE_INNER_TYPES(orientation_sensor)


class orientation_sensor::orientation_sensor
        : public sensors::sensor
{
public constructors:
    orientation_sensor() = default;
    orientation_sensor(detail::orientation_sensor_options_t&& options = {});

public js_methods:
    auto populate_matrix(detail::rotation_matrix_type_t target_matrix);

public js_properties:
    ext::property<const std::unique_ptr<ext::number<double>>> quaternion;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ORIENTATION_SENSOR_HPP
