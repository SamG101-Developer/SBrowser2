module;
#include "ext/macros/pimpl.hpp"
#include <memory>


export module apis.dom.abstract_iterator_private;
import apis._.dom_object_private;
import ext.boolean;
import ext.memory;
import ext.number;

namespace dom {class node_filter;}
namespace dom {class node;}


DEFINE_PRIVATE_CLASS(dom, abstract_iterator)
        : virtual dom_object_private
{
    MAKE_QIMPL(abstract_iterator);

    ext::boolean active_flag;

    std::observer_ptr<node> root;
    ext::number<ulong> what_to_show;
    std::unique_ptr<node_filter> filter;
};
