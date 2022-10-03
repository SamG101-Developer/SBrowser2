#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_RECORD_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_RECORD_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private"

#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::mutations, mutation_record) : virtual dom_object_private
{
    ext::string type;
    ext::string attribute_name;
    ext::string attribute_namespace;
    ext::string old_value;

    nodes::node* target;
    nodes::node* previous_sibling;
    nodes::node* next_sibling;

    ext::vector<nodes::node*> added_nodes;
    ext::vector<nodes::node*> removed_nodes;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MUTATIONS_MUTATION_RECORD_PRIVATE_HPP
