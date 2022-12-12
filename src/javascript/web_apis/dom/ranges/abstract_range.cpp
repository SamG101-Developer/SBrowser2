module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.dom.abstract_range;
import apis.dom.abstract_range_private;
import apis.dom.node;

import ext.boolean;
import ext.number;
import ext.tuple;

import js.env.module_type;


auto dom::abstract_range::get_start_container() const -> node*
{
    // The 'start_container' getter returns the node of the 'start' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->start->node.get();
}


auto dom::abstract_range::get_start_offset() const -> ext::number<ulong>
{
    // The 'start_offset' getter returns the offset of the 'start' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->start->offset;
}


auto dom::abstract_range::get_end_container() const -> node*
{
    // The 'end_container' getter returns the node of the 'end' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->end->node.get();
}


auto dom::abstract_range::get_end_offset() const -> ext::number<ulong>
{
    // The 'end_offset' getter returns the offset of the 'end' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->end->offset;
}


auto dom::abstract_range::get_collapsed() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->is_range_collapsed(this);
}


auto dom::abstract_range::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("startContainer", &abstract_range::get_start_container)
        .property("startOffset", &abstract_range::get_start_offset)
        .property("endContainer", &abstract_range::get_end_container)
        .property("endOffset", &abstract_range::get_end_offset)
        .property("collapsed", &abstract_range::get_collapsed)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
