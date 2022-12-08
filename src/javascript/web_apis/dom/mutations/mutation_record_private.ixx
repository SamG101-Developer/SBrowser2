module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mutation_record_private;
import apis._.dom_object_private;
import ext.string;
import ext.vector;

namespace dom {class node;}



DEFINE_PRIVATE_CLASS(dom, mutation_record)
        : virtual dom_object_private
{
    MAKE_QIMPL(mutation_record);

    ext::string type;
    ext::string attribute_name;
    ext::string attribute_namespace;
    ext::string old_value;

    nodes::node* target;
    nodes::node* previous_sibling;
    nodes::node* next_sibling;

    ext::vector<node*> added_nodes;
    ext::vector<node*> removed_nodes;
};
