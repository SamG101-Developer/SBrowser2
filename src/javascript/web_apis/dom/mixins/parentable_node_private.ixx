module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.parentable_node_private;
import apis._.dom_object_private;
import ext.casting;
import ext.functional;
import ext.ranges;

namespace dom {class element;}


DEFINE_PRIVATE_CLASS(dom, parentable_node)
        : virtual dom_object_private
{
    parentable_node();
    ranges::any_helpful_view<element*> children;
};
