module;
#include "ext/macros.hpp"


export module apis.dom.node_filter:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom, node_filter) final
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(node_filter);

public:
    node_iterator::accept_callback_t accept_node_callback;
};
