#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_ABSTRACT_QUEUING_STRATEGY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_ABSTRACT_QUEUING_STRATEGY_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace streams::queuing {class abstract_queuing_strategy;}
namespace streams::queuing {class abstract_queuing_strategy_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(streams)


class streams::queuing::abstract_queuing_strategy
        : virtual public dom_object
{
public constructors:
    abstract_queuing_strategy(detail::queueing_strategy_init_t&& init);
    MAKE_PIMPL(abstract_queuing_strategy);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(high_water_mark, detail::high_water_mark_t);
    virtual DEFINE_GETTER(size, ext::function<>) = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_QUEUING_ABSTRACT_QUEUING_STRATEGY_HPP
