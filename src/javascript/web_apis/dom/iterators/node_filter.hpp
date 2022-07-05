#pragma once
#ifndef SBROWSER2_NODE_FILTER_HPP
#define SBROWSER2_NODE_FILTER_HPP

#include <web_apis/dom_object.hpp>
namespace dom::node_iterators {class node_filter;}


class dom::node_iterators::node_filter
        : public virtual web_apis::dom_object
{
public aliases:
    using accept_callback_t = std::function<ext::number<ushort>(nodes::node*)>;

public constructors:
    node_filter();

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
    ext::property<accept_callback_t> accept_node;
    
public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_NODE_FILTER_HPP
