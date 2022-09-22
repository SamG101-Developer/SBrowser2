#pragma once
#ifndef SBROWSER2_STATIC_RANGE_HPP
#define SBROWSER2_STATIC_RANGE_HPP

#include "dom/ranges/abstract_range.hpp"
namespace dom::node_ranges {class static_range;}

#include "ext/map.hpp"
#include INCLUDE_INNER_TYPES(dom)

#include "dom/ranges/static_range_private.hpp"


class dom::node_ranges::static_range
        : public abstract_range
{
public constructors:
    static_range(detail::static_range_init_t&& init = {});

public cpp_members:
    MAKE_PIMPL(static_range);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_STATIC_RANGE_HPP
