#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_ABSTRACT_QUEUING_STRATEGY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_ABSTRACT_QUEUING_STRATEGY_PRIVATE_HPP

#include "ext/pimpl.ixx"

namespace streams::queuing {class abstract_queuing_strategy;}

#include INCLUDE_INNER_TYPES(streams)


DEFINE_PRIVATE_CLASS(streams::queuing, abstract_queuing_strategy) : dom_object_private
{
    MAKE_QIMPL(abstract_queuing_strategy);

    detail::high_water_mark_t high_water_mark;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_ABSTRACT_QUEUING_STRATEGY_PRIVATE_HPP
