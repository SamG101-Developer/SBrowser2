module;
#include "ext/macros.hpp"


export module apis.dom.mixins.non_element_parent_node;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom::mixins, non_element_parent_node)
        : public virtual dom_object
{
public constructors:
    non_element_parent_node();
    MAKE_PIMPL(non_element_parent_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    auto get_element_by_id(ext::string_view id) -> element*;
};
