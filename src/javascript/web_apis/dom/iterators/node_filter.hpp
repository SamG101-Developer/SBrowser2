#pragma once
#ifndef SBROWSER2_NODE_FILTER_HPP
#define SBROWSER2_NODE_FILTER_HPP

#include "dom_object.hpp"
namespace dom::node_iterators {class node_filter;}

#include "ext/functional.hpp"
#include INCLUDE_INNER_TYPES(dom)

#include "dom/iterators/node_filter_private.hpp"


class dom::node_iterators::node_filter
        : public virtual dom_object
{
public constructors:
    node_filter();
    MAKE_PIMPL(node_filter);
    MAKE_V8_AVAILABLE;

public js_static_constants:
    constexpr static const ext::number<ushort> FILTER_ACCEPT = 1;
    constexpr static const ext::number<ushort> FILTER_REJECT = 2;
    constexpr static const ext::number<ushort> FILTER_SKIP   = 3;

    constexpr static const ext::number<ulong> SHOW_ELEMENT                 = 0x1;
    constexpr static const ext::number<ulong> SHOW_ATTRIBUTE               = 0x2;
    constexpr static const ext::number<ulong> SHOW_TEXT                    = 0x4;
    constexpr static const ext::number<ulong> SHOW_CDATA_SECTION           = 0x8;
    constexpr static const ext::number<ulong> SHOW_PROCESSING_INSTRUCTION  = 0x40;
    constexpr static const ext::number<ulong> SHOW_COMMENT                 = 0x80;
    constexpr static const ext::number<ulong> SHOW_DOCUMENT                = 0x100;
    constexpr static const ext::number<ulong> SHOW_DOCUMENT_TYPE           = 0x200;
    constexpr static const ext::number<ulong> SHOW_DOCUMENT_FRAGMENT       = 0x400;
    constexpr static const ext::number<ulong> SHOW_ALL                     = 0xFFFFFFFF;
    
public js_properties:
    DEFINE_GETTER(accept_node, detail::accept_callback_t) {return d_ptr->accept_node_callback;}
    DEFINE_SETTER(accept_node, detail::accept_callback_t) {return d_ptr->accept_node_callback = std::move(new_accept_node);}
};


#endif //SBROWSER2_NODE_FILTER_HPP
