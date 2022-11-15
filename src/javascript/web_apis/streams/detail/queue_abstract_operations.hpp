#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_QUEUE_ABSTRACT_OPERATIONS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_QUEUE_ABSTRACT_OPERATIONS_HPP


#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(streams)

namespace streams::detail
{
    auto extract_high_water_mark(
            queueing_strategy_t&& strategy,
            high_water_mark_t default_hwm)
            -> high_water_mark_t;

    auto extract_size_algorithm(
            queueing_strategy_t&& strategy)
            -> size_algorithm_t;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_QUEUE_ABSTRACT_OPERATIONS_HPP
