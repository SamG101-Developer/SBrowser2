module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <function2/function2.hpp>


export module apis.dom.node_filter;
import apis.dom_object;
import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, node_filter) final
        : public virtual dom_object
{
public typedefs:
    using accept_callback_t = ext::unique_function<ext::number<ushort>(const node*)>;

public constructors:
    node_filter();
    MAKE_PIMPL(node_filter);
    MAKE_V8_AVAILABLE(WINDOW);

public js_static_constants:
    constexpr static const ext::number<ushort> FILTER_ACCEPT = 1;
    constexpr static const ext::number<ushort> FILTER_REJECT = 2;
    constexpr static const ext::number<ushort> FILTER_SKIP   = 3;

    constexpr static const ext::number<ulong> SHOW_ELEMENT = 0x1;
    constexpr static const ext::number<ulong> SHOW_ATTRIBUTE = 0x2;
    constexpr static const ext::number<ulong> SHOW_TEXT = 0x4;
    constexpr static const ext::number<ulong> SHOW_CDATA_SECTION = 0x8;
    constexpr static const ext::number<ulong> SHOW_PROCESSING_INSTRUCTION = 0x40;
    constexpr static const ext::number<ulong> SHOW_COMMENT = 0x80;
    constexpr static const ext::number<ulong> SHOW_DOCUMENT = 0x100;
    constexpr static const ext::number<ulong> SHOW_DOCUMENT_TYPE = 0x200;
    constexpr static const ext::number<ulong> SHOW_DOCUMENT_FRAGMENT = 0x400;
    constexpr static const ext::number<ulong> SHOW_ALL = 0xFFFFFFFF;
    
private js_properties:
    DEFINE_GETTER(accept_node, accept_callback_t);
    DEFINE_SETTER(accept_node, accept_callback_t&&);
};
