#pragma once
#ifndef SBROWSER2_STATIC_RANGE_HPP
#define SBROWSER2_STATIC_RANGE_HPP

#include "dom/ranges/abstract_range.hpp"
namespace dom::node_ranges {class static_range;}
namespace dom::node_ranges {class static_range_private;}

#include INCLUDE_INNER_TYPES(dom)


class dom::node_ranges::static_range
        : public abstract_range
{
public constructors:
    static_range(detail::static_range_init_t&& init = {});
    MAKE_PIMPL(static_range);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_STATIC_RANGE_HPP
