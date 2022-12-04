#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP


#include INCLUDE_INNER_TYPES(sensors)
namespace ambient_light_sensor {class ambient_light_sensor;}


namespace ambient_light_sensor::detail
{
    ext::number<int> illuminance_rounding_multiple = 1;
    ext::number<int> illuminance_threshold_value = 1;

    auto construct_ambient_light_sensor_object(
            ambient_light_sensor* sensor,
            sensors::detail::sensor_options_t&& options)
            -> ambient_light_sensor;

    auto ambient_light_threshold_check_algorithm(
            sensors::detail::sensor_reading_t&& new_reading,
            sensors::detail::sensor_reading_t&& latest_reading)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
