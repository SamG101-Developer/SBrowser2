module;
#include "ext/macros.hpp"


export module apis.dom.mutation_record:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, mutation_record)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(mutation_record);

public:
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
