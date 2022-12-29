module;
#include "ext/macros/pimpl.hpp"
#include <memory>


export module apis.dom.mutation_observer_private;
import apis.dom_object_private;
#
import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, mutation_observer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(mutation_observer);

public:
    mutation_callback_t callback;
    ext::vector<node*> node_list;
    ext::queue<std::unique_ptr<mutation_record>> record_queue;
};
