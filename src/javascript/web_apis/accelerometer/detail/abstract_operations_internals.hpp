#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/keywords.hpp"
#include USE_INNER_TYPES(accelerometer)
namespace accelerometer {class accelerometer;}


namespace accelerometer::detail
{
    auto construct_accelerometer_object(
            accelerometer* sensor,
            accelerometer_sensor_options_t&& options)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
