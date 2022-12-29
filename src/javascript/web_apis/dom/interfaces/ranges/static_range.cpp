module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <tuplet/tuple.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.dom.static_range;
import apis.dom.static_range_private;
import apis.dom.node;
import apis.dom.node_private;
import apis.dom.document_type;
import apis.dom.attr;
import apis.dom.detail;
import apis.dom.types;

import ext.core;

import js.env.module_type;


dom::static_range::static_range(static_range_init_t&& init)
{
    INIT_PIMPL; ACCESS_PIMPL;

    using enum detail::dom_exception_error_t;

    d->start->node = init[u"startContainer"].to<node*>();
    d->end->node = init[u"endContainer"].to<node*>();
    d->start->offset = init[u"startOffset"].to<ext::number<ulong>>();
    d->end->offset = init[u"endOffset"].to<ext::number<ulong>>();

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [d] {return dom_multi_cast<document_type*, attr*>(d->start->node.get());},
            u8"Start container can not be a DocumentType or Attribute node");

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [d] {return dom_multi_cast<document_type*, attr*>(d->end->node.get());},
            u8"End container can not be a DocumentType or Attribute node");
}


auto dom::static_range::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<abstract_range>()
        .ctor<static_range_init_t&&>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
