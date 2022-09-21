#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(magnetometer)
namespace magnetometer {class magnetometer;}


namespace magnetometer::detail
{
    auto construct_magnetometer_object(
            magnetometer* sensor,
            magnetometer_sensor_options_t&& options)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
