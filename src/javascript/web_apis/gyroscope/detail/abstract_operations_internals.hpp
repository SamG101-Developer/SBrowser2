#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(gyroscope)
namespace gyroscope {class gyroscope;}


namespace gyroscope::detail
{
    auto construct_gyroscope_object(
            gyroscope* sensor,
            gyroscope_sensor_options_t&& options)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
