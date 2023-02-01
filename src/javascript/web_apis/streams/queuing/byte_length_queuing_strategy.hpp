#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_BYTE_LENGTH_QUEUING_STRATEGY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_BYTE_LENGTH_QUEUING_STRATEGY_HPP

// Inheritance Includes & This Class
#include "abstract_queuing_strategy.hpp"
namespace streams::queuing {class byte_length_queuing_strategy;}
namespace streams::queuing {class byte_length_queuing_strategy_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(streams)


class streams::queuing::byte_length_queuing_strategy
        : public abstract_queuing_strategy
{
public constructors:
    byte_length_queuing_strategy(detail::queueing_strategy_init_t&& init);
    MAKE_PIMPL(byte_length_queuing_strategy);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(size, ext::function<>) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_BYTE_LENGTH_QUEUING_STRATEGY_HPP
