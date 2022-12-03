#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(proximity)
namespace proximity {class proximity;}


namespace proximity::detail
{
    auto construct_proximity_sensor(
            proximity* sensor,
            proximity_sensor_options_t&& options)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_DETAIL_ABSTRACT_OPERATIONS_INTERNALS_HPP
