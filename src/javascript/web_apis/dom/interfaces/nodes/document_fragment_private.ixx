module;
#include "ext/macros.hpp"


export module apis.dom.document_fragment:p;
import apis.dom.node;
import apis.dom.mixins.non_element_parent_node;
import apis.dom.mixins.parentable_node;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, document_fragment)
        : dom::node_private
        , dom::non_element_parent_node_private
        , dom::parentable_node_private
{
public:
    MAKE_QIMPL(document_fragment);

public:
    std::observer_ptr<element> host;
};
