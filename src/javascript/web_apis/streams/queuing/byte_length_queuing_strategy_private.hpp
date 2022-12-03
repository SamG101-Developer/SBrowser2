#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_BYTE_LENGTH_QUEUING_STRATEGY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_BYTE_LENGTH_QUEUING_STRATEGY_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "abstract_queuing_strategy_private.hpp"
namespace streams::other {class byte_length_queuing_strategy;}


DEFINE_PRIVATE_CLASS(streams::queuing, byte_length_queuing_strategy) : abstract_queuing_strategy_private
{
    MAKE_QIMPL(byte_length_queuing_strategy);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_BYTE_LENGTH_QUEUING_STRATEGY_PRIVATE_HPP
