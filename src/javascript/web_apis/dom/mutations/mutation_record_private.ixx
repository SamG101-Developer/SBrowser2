module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mutation_record_private;
import apis._.dom_object_private;
import ext.memory;
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

    std::observer_ptr<node> target;
    std::observer_ptr<node> previous_sibling;
    std::observer_ptr<node> next_sibling;

    ext::vector<node*> added_nodes;
    ext::vector<node*> removed_nodes;
};
