module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.document_type_private;
import apis.dom.node_private;
import apis.dom.mixins.child_node_private;

import ext.string;


DEFINE_PRIVATE_CLASS(dom, document_type) final
        : dom::node_private
        , dom::child_node_private
{
    MAKE_QIMPL(document_type);

    ext::string name;
    ext::string public_id;
    ext::string system_id;
};