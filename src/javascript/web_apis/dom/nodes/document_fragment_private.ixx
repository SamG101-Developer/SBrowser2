module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.document_fragment_private;
import apis.dom.node_private;
import apis.dom.mixins.non_element_parent_node_private;
import apis.dom.mixins.parentable_node_private;

import ext.memory;

namespace dom {class element;}


DEFINE_PRIVATE_CLASS(dom, document_fragment)
        : dom::node_private
        , dom::non_element_parent_node_private
        , dom::parentable_node_private
{
    MAKE_QIMPL(document_fragment);

    std::observer_ptr<element> host;
};
