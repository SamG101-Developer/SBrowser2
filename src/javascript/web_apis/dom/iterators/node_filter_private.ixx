module;
#include "ext/macros/pimpl.hpp"

module apis.dom.node_filter_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(dom, node_filter) final
        : virtual dom_object_private
{
    MAKE_QIMPL(node_filter);
    node_iterator::accept_callback_t accept_node_callback;
};
