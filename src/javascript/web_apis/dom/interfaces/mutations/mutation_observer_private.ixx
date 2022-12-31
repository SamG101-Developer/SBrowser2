module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.dom.mutation_observer:p;
import apis.dom_object;
#
import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, mutation_observer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(mutation_observer);
    using mutation_observer_init_t = ext::map<ext::string, ext::any>;
    using mutation_callback_t = ext::unique_function<void(ext::vector<mutation_record*>&&, mutation_observer*)>;

public:
    mutation_callback_t callback;
    ext::vector<node*> node_list;
    ext::queue<std::unique_ptr<mutation_record>> record_queue;
};
