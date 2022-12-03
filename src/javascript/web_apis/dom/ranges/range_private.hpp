#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_RANGE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_RANGE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/ranges/abstract_range_private.hpp"


DEFINE_PRIVATE_CLASS(dom::node_ranges, range)
        : abstract_range_private
{
    MAKE_QIMPL(range);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_RANGE_PRIVATE_HPP
