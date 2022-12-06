module;
#include "ext/macros/pimpl.hpp"


module apis.dom.tree_walker_private;
import apis.dom.abstract_iterator_private;
import ext.memory;

namespace dom {class node;}



DEFINE_PRIVATE_CLASS(dom, tree_walker)
        : dom::abstract_iterator_private
{
    MAKE_QIMPL(tree_walker);

    std::observer_ptr<node> current;
};
