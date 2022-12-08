#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_STATIC_RANGE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_STATIC_RANGE_PRIVATE_HPP

#include "ext/pimpl.ixx"



DEFINE_PRIVATE_CLASS(dom::node_ranges, static_range)
        : abstract_range_private
{
    MAKE_QIMPL(static_range);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_STATIC_RANGE_PRIVATE_HPP
