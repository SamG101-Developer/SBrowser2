#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_OBSERVER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_OBSERVER_PRIVATE_HPP

#include "dom_object_private"

#include "ext/pimpl.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::mutations, mutation_observer) : virtual dom_object_private
{
    detail::mutation_callback_t m_callback;
    ext::vector<nodes::node*> m_node_list;
    ext::queue<mutations::mutation_record*> m_record_queue;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_OBSERVER_PRIVATE_HPP
