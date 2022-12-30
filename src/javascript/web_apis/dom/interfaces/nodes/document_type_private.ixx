module;
#include "ext/macros.hpp"


export module apis.dom.document_type:p;
import apis.dom.node;
import apis.dom.mixins.child_node;

import ext.core;


DEFINE_PRIVATE_CLASS(dom, document_type) final
        : dom::node_private
        , dom::child_node_private
{
public:
    MAKE_QIMPL(document_type);

public:
    ext::string name;
    ext::string public_id;
    ext::string system_id;
};
