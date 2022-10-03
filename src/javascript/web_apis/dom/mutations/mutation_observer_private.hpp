#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_OBSERVER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_OBSERVER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include "ext/queue.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::mutations, mutation_observer) : virtual dom_object_private
{
    detail::mutation_callback_t callback;
    ext::vector<nodes::node*> node_list;
    ext::queue<std::unique_ptr<mutations::mutation_record>> record_queue;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_OBSERVER_PRIVATE_HPP
