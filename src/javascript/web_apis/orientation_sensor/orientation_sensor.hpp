#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ORIENTATION_SENSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ORIENTATION_SENSOR_HPP


namespace orientation_sensor {class orientation_sensor;}
namespace orientation_sensor {class orientation_sensor_private;}

#include INCLUDE_INNER_TYPES(orientation_sensor)


class orientation_sensor::orientation_sensor
        : public sensors::sensor
{
public constructors:
    orientation_sensor(detail::orientation_sensor_options_t&& options);
    DOM_CTORS(orientation_sensor);
    MAKE_PIMPL(orientation_sensor);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto populate_matrix(ext::vector<ext::number<double>>& target_matrix) -> void;
    auto populate_matrix(css::geometry::dom_matrix* target_matrix) -> void;

private js_properties:
    DEFINE_GETTER(quaternion, ext::vector_view<ext::number<double>>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR_ORIENTATION_SENSOR_HPP
