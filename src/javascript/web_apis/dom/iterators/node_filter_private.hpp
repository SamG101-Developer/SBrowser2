#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_NODE_FILTER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_NODE_FILTER_PRIVATE_HPP

#include "dom_object_private"

#include "ext/pimpl.hpp"

#include INCLUDE_INNER_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom::node_iterators, node_filter) : virtual dom_object_private
{
    detail::accept_callback_t accept_node_callback;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_NODE_FILTER_PRIVATE_HPP