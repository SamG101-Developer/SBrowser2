module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.abstract_iterator;
import apis._.dom_object;
import ext.number;
import ext.tuple;
import ext.type_traits;
import js.env.module_type;

namespace dom {class node;}
namespace dom {class node_filter;}


DEFINE_PUBLIC_CLASS(dom, abstract_iterator)
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(abstract_iterator);
    MAKE_PIMPL(abstract_iterator);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(filter, node_filter*);
    DEFINE_GETTER(root, node*);
    DEFINE_GETTER(what_to_show, ext::number<ulong>);
};
