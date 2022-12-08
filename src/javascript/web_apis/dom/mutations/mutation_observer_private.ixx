module;
#include "ext/macros/pimpl.hpp"
#include <memory>


export module apis.dom.mutation_observer_private;
import apis._.dom_object_private;
import ext.vector;
import ext.queue;

namespace dom {class node;}
namespace dom {class mutation_record;}


DEFINE_PRIVATE_CLASS(dom, mutation_observer)
        : virtual dom_object_private
{
    MAKE_QIMPL(mutation_observer);

    mutation_callback_t callback;
    ext::vector<node*> node_list;
    ext::queue<std::unique_ptr<mutation_record>> record_queue;
};
