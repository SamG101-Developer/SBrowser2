#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include USE_INNER_TYPES(sensors)
namespace ambient_light_sensor {class ambient_light_sensor;}


namespace ambient_light_sensor::detail
{
    auto construct_ambient_light_sensor_object(
            sensors::detail::sensor_options_t&& options)
            -> ambient_light_sensor;

    auto ambient_light_threshold_check_algorithm(
            const sensors::detail::sensor_reading_t& new_reading,
            const sensors::detail::sensor_reading_t& latest_reading)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
