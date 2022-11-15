#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_COUNT_QUEUING_STRATEGY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_COUNT_QUEUING_STRATEGY_HPP

// Inheritance Includes & This Class
#include "abstract_queuing_strategy.hpp"
namespace streams::queuing {class count_queuing_strategy;}
namespace streams::queuing {class count_queuing_strategy_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(streams)


class streams::queuing::count_queuing_strategy
        : public abstract_queuing_strategy
{
public constructors:
    count_queuing_strategy();
    MAKE_PIMPL(count_queuing_strategy);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(size, ext::function<>) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_COUNT_QUEUING_STRATEGY_HPP
