#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_ABSTRACT_RANGE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_ABSTRACT_RANGE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(dom)


DEFINE_PRIVATE_CLASS(dom::node_ranges, abstract_range) : virtual dom_object_private
{
    std::unique_ptr<detail::boundary_point_t> start;
    std::unique_ptr<detail::boundary_point_t> end;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_RANGES_ABSTRACT_RANGE_PRIVATE_HPP
