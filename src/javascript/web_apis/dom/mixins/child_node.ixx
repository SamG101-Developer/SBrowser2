module;
#include "ext/macros.hpp"


export module apis.dom.mixins.child_node;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom::mixins, child_node)
        : public virtual dom_object
{
public constructors:
    child_node();
    MAKE_PIMPL(child_node);
    MAKE_V8_AVAILABLE(MIXIN);

private js_methods:
    template <ext::type_is<node*, ext::string> ...Args> auto before(Args&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...Args> auto after(Args&&... nodes) -> node*;
    template <ext::type_is<node*, ext::string> ...Args> auto replace_with(Args&&... nodes) -> node*;
    auto remove() -> node*;
};
